#include "Jsonhandler.h"

json::object JsonHandler::processRequest( json::value& request, std::shared_ptr<System> system)
{
    std::string command = request.as_object()["command"].as_string().c_str();

    if(command == "login")
    {
        return handleLogin(request, system);

    }
    else if(command == "addProvider")
    {
        return addProvider(request, system);
    }
    else if(command== "loginProvider")
    {
        return loginProvider(request, system);
    }
    else if(command == "addUser")
    {
	return addUser(request, system);
    }
    else
    {
        json::object response;
        response["error"]= "Unknown command.";
        return response;
    }
}

json::object JsonHandler::handleLogin( json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    QString qName = QString::fromStdString(name);
    QString qPass = QString::fromStdString(password);
    if(system->login(qName, qPass))
    {
	response["status"] = "success";
	response["command"] = "login";
        response["message"] = name + " Logged in successfully.";
    }
    else
    {
	response["status"] = "failure";
	response["command"] = "login";
        response["message"] = "Invalid Username or password.";
    }
    return response;
}

json::object JsonHandler::addProvider( json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();
    Provider p(name, password, "Default", 0);
    system->addProvider(p);
    response["status"]= "success";
    response["message"] = name + " signed in as provider successfully.";
    response["command"] = "addProvider";
    return response;
}

json::object JsonHandler::loginProvider(json::value& request, std::shared_ptr<System> system)
{
    json::object response;
    std::string name = request.as_object()["name"].as_string().c_str();
    std::string password = request.as_object()["password"].as_string().c_str();

    QString qName = QString::fromStdString(name);
    QString qPass = QString::fromStdString(password);
    if(system->loginProvider(qName, qPass))
    {
	response["status"] = "success";
        response["message"] = name + " logged in successfuly.";
	response["command"] = "loginProvider";
    }
    else
    {
	response["status"] = "failure";
        response["message"] = "Invalid Username or password";
	response["command"] = "loginProvider";
    }
    return response;
}

json::object JsonHandler::addUser(json::value& request, std::shared_ptr<System> system)
{
	json::object response;
	std::string name = request.as_object()["name"].as_string().c_str();
	std::string password = request.as_object()["password"].as_string().c_str();

	QString qName = QString::fromStdString(name);
	QString qPass = QString::fromStdString(password);

	system->registerUser(qName, qPass);
        response["status"]= "success";
        response["message"] = name + " signed in as user successfully.";
	response["command"] = "addUser";
	return response;
}
