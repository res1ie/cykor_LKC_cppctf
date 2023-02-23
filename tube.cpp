#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <iostream>

//need boost library
//compiler option -lboost_system -pthread

namespace bp = boost::process;
using boost::asio::ip::tcp;

class Process {
public:
    Process(std::string command) {
        out_ = std::make_unique<bp::ipstream>();
        in_ = std::make_unique<bp::opstream>();

        child_ = std::make_unique<bp::child>(command, bp::std_out > *out_, bp::std_in < *in_);
    }

    void send(std::string input) {
        *in_ << input;
    }

    void sendline(std::string input)
    {
        *in_ << input << std::endl;
    }


    std::string recvline() {
        std::string line;
        if (std::getline(*out_, line)) {
            return line;
        } else {
            return "";
        }
    }
// this recv function is not working, need some update
/*
    std::string recvuntil(std::string delim) {
        boost::asio::streambuf response;
        boost::asio::read_until(out_, &response[0], delim);
        return boost::asio::buffer_cast<const char*>(response.data());
    }

    
    std::string recv(int num) {
        std::string response(num, '\0');
        boost::asio::read(*out_, boost::asio::buffer(response.data(), num));
        return response;
    }
/*
    std::string recvline() {
        return recvuntil("\n");
    }
*/
    ~Process() {
        if (child_->running()) {
            child_->wait();
        }
    }

private:
    std::unique_ptr<bp::ipstream> out_;
    std::unique_ptr<bp::opstream> in_;
    std::unique_ptr<bp::child> child_;
};

class remote {
public:
    remote(std::string server, std::string port)
        : io_context_(), resolver_(io_context_), socket_(io_context_) {
        resolve(server, port);
        connect();
    }

    void send(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }

    void sendline(const std::string& message) {
        std::string en = "\n";
        boost::asio::write(socket_, boost::asio::buffer(message + en));
    }

    std::string recvline() {
        return recvuntil("\n");
    }

    std::string recvuntil(const std::string& target) {
        std::string response;
        char c;

        while (true) {
            boost::asio::read(socket_, boost::asio::buffer(&c, 1));
            response += c;

            if (response.find(target) != std::string::npos) {
                break;
            }
        }
        return response;
    }

    std::string recv(int num) {
        std::string response;
        char c;
        int i = 0;
        while (i < num) {
            boost::asio::read(socket_, boost::asio::buffer(&c, 1));
            response += c;
            i++;
        }
        return response;
    }

private:
    void resolve(const std::string& server, const std::string& port) {
        tcp::resolver::query query(server, port);
        endpoints_ = resolver_.resolve(query);
    }

    void connect() {
        boost::asio::connect(socket_, endpoints_);
    }

    boost::asio::io_context io_context_;
    tcp::resolver resolver_;
    tcp::socket socket_;
    tcp::resolver::results_type endpoints_;
};

std::string PackInt(long long value, int bits) {
    if (bits % 8 != 0 || bits > 64) {
        throw std::invalid_argument("Invalid bit size");
    }
    std::string result(bits / 8, '\0');
    for (int i = 0; i < bits / 8; i++) {
        result[i] = static_cast<char>(value >> (i * 8));
    }
    return result;
}

std::string p8(long long value)
{
    return PackInt(value, 8);
}

std::string p16(long long value)
{
    return PackInt(value, 16);
}

std::string p32(long long value)
{
    return PackInt(value, 32);
}

std::string p64(long long value)
{
    return PackInt(value, 64);
}

long long UnpackInt(const std::string& packed, int bits) {
    if (bits % 8 != 0 || bits > 64) {
        throw std::invalid_argument("Invalid bit size");
    }
    long long result = 0;
    for (int i = 0; i < bits / 8; i++) {
        result |= static_cast<long long>(static_cast<unsigned char>(packed[i])) << (i * 8);
    }
    return result;
}

long long u8(const std::string& packed)
{
    return UnpackInt(packed, 8);
}

long long u16(const std::string& packed)
{
    return UnpackInt(packed, 16);
}

long long u32(const std::string& packed)
{
    return UnpackInt(packed, 32);
}

long long u64(const std::string& packed)
{
    return UnpackInt(packed, 64);
}

/*
int main(int argc, char* argv[]) {
    std::cout << "start" << std::endl;
    remote client("pwnable.kr", "9000");

    std::cout << "start2" << std::endl;
    client.sendline("nob");

    std::string response = client.recvuntil("me");
    std::cout << "Response: " << response << std::endl;

    return 0;
}*/