#include <iostream>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include "System.h"
#include "Jsonhandler.h"
namespace json = boost::json;
using namespace std;

using boost::asio::ip::tcp;

void handleClient(std::shared_ptr<tcp::socket> socket, std::shared_ptr<System> system) {
    auto data = std::make_shared<std::string>(1024, '\0');

    socket->async_read_some(boost::asio::buffer(&(*data)[0], 1024),
                            [socket, data, system](const boost::system::error_code& ec, std::size_t len) {
                                if (!ec) {
                                    std::string recieved_str = data->substr(0, len);
                                    cout << "Recieved: "<< recieved_str << endl;
                                    json::value request_json = json::parse(recieved_str);


                                    json::object response= JsonHandler::processRequest(request_json, system);
                                    string response_str = json::serialize(response);
                                    boost::asio::async_write(*socket, boost::asio::buffer(response_str),
                                        [socket, system](const boost::system::error_code& ec, std::size_t /*length*/) {
                            if (!ec) {
                                handleClient(socket, system);
                            }
                        });
                                } else {
                                    cout << "Client disconnected safely." << endl;
                                }
                            });
}

void waitForClient(tcp::acceptor &acceptor, boost::asio::io_context &context, std::shared_ptr<System> system ){
    // Create the socket in a shared_ptr
    auto socket = std::make_shared<tcp::socket>(context);

    acceptor.async_accept(*socket, [socket, &acceptor, &context, system](const boost::system::error_code& ec) {
        if(!ec) {
            cout << "Client connected." << endl;
            handleClient(socket, system);
            waitForClient(acceptor, context, system);
        }
    });
}

int main()
{

    auto system = std::make_shared<System>();

    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

    std::cout << "Wating for connection on the port 12345" << std::endl;

    waitForClient(acceptor, io_context, system);
        // tcp::socket socket(io_context);
        // acceptor.accept(socket);

        // std::cout << "A client has connected to the server." << std::endl;
    io_context.run();

}
