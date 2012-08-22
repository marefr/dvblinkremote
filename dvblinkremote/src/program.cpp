/***************************************************************************
 * Copyright (C) 2012 Marcus Efraimsson.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>
#include "command_interpreter.h"
#include "util.h"
#include "libdvblinkremote\dvblinkremote.h"
#include "libdvblinkremote\dvblinkremotehttp.h"
#include "libdvblinkremote\curlhttpclient.h"

using namespace dvblinkremote;
using namespace dvblinkremotehttp;

static void Test(std::string type, std::string message) 
{
  if (type != dvblinkremotehttp::DVBLINK_REMOTE_HTTP_CURL_DEBUG_MESSAGE_TYPE_RECIEVED_RESPONSE_DATA) { 
    std::cout << "DEBUG: " + message << std::endl;
  }
}

void PrintUsage()
{
  std::string copyright = "";
  std::string version = "";
  DVBLinkRemote::GetCopyrightNotice(copyright);
  DVBLinkRemote::GetVersion(version);

  std::cout << "DVBLink Remote:" << std::endl;
  std::cout << "  Command line tool for communicating with a DVBLink Connect! server." << std::endl;
  std::cout << std::endl;
  std::cout << "Usage:" << std::endl;
  std::cout << "  dvblinkremote -h <hostname> -p <port> -cid <client id>" << std::endl;
  std::cout << "                [-u <username>] [-pwd <password>] [-x <proxy server>] [-v]" << std::endl;
  std::cout << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -h    The host address of the DVBLink Connect! server." << std::endl;
  std::cout << "        This option is required." << std::endl;
  std::cout << std::endl;
  std::cout << "  -p    The base streaming port of the DVBLink Connect! server." << std::endl;
  std::cout << "        This option is required." << std::endl;
  std::cout << std::endl;
  std::cout << "  -cid  A unique identifier of the client that request a transcoded stream." << std::endl;
  std::cout << "        This option is required." << std::endl;
  std::cout << std::endl;
  std::cout << "  -u    User name for authentication towards the DVBLink Connect! server." << std::endl;
  std::cout << "        This option is optional." << std::endl;
  std::cout << std::endl;
  std::cout << "  -pwd  Password for authentication towards the DVBLink Connect! server." << std::endl;
  std::cout << "        This option is optional." << std::endl;
  std::cout << std::endl;
  std::cout << "  -x    A proxy server URL for usage with Fiddler or similar." << std::endl;
  std::cout << "        This option is optional." << std::endl;
  std::cout << std::endl;
  std::cout << "  -v    Enable verbose logging. This option is optional." << std::endl;
  std::cout << std::endl;
  std::cout << "Copyright notice:" << std::endl;
  std::cout << "  libdvblinkremote " << version << ", Copyright (C) " << copyright << std::endl;
}

int main(int argc, char * argv[]) 
{
  char* argHostName = NULL;
  char* argPort = NULL;
  long port = -1;
  char* argUsername = NULL;
  char* argPassword = NULL;
  char* argClientId = NULL;
  char* argProxyServer = NULL;
  bool argVerbose = false;

  if (CmdOptionExists(argv, argv + argc, "-h"))
  {
    argHostName = GetCmdOption(argv, argv + argc, "-h");
  }

  if (CmdOptionExists(argv, argv + argc, "-p"))
  {
    argPort = GetCmdOption(argv, argv + argc, "-p");

    long tempPort;

    if (StringToLong(tempPort, argPort, std::dec)) {
      port = tempPort;
    }
  }

  if (CmdOptionExists(argv, argv + argc, "-u"))
  {
    argUsername = GetCmdOption(argv, argv + argc, "-u");
  }

  if (CmdOptionExists(argv, argv + argc, "-pwd"))
  {
    argPassword = GetCmdOption(argv, argv + argc, "-pwd");
  }

  if (CmdOptionExists(argv, argv + argc, "-cid"))
  {
    argClientId = GetCmdOption(argv, argv + argc, "-cid");
  }

  if (!argHostName || argPort <= 0 || !argUsername || !argPassword || !argClientId) {
    PrintUsage();
    return 0;
  }

  if (CmdOptionExists(argv, argv + argc, "-x"))
  {
    argProxyServer = GetCmdOption(argv, argv + argc, "-x");
  }

  if (CmdOptionExists(argv, argv + argc, "-v"))
  {
    argVerbose = true;
  }

  std::string hostAddress = argHostName;
  std::string username = argUsername;
  std::string password = argPassword;
  std::string clientId = argClientId;
  std::string proxyServer = "";
  
  if (argProxyServer) {
    proxyServer = argProxyServer;
  }

  CurlHttpClient* httpClient = NULL; 

  if (!proxyServer.empty() && argVerbose) {
    httpClient = new CurlHttpClient(proxyServer, *Test);
  }
  else if (!proxyServer.empty()) {
    httpClient = new CurlHttpClient(proxyServer);
  }
  else if (argVerbose) {
    httpClient = new CurlHttpClient(*Test);
  }
  else {
    httpClient = new CurlHttpClient();
  }

  IDVBLinkRemoteConnection* dvblinkRemoteCommunication = DVBLinkRemote::Connect((HttpClient&)*httpClient, hostAddress, port, username, password);
  CommandInterpreter* commandInterpreter = new CommandInterpreter(*dvblinkRemoteCommunication, hostAddress, clientId);
  
  while (true) {
    commandInterpreter->PrintCommands();

    std::string command;
    std::cout << std::endl << "Enter command: ";
    getline(std::cin, command);
    ToLowerCase(command);

    std::cout << std::endl;

    int ret = commandInterpreter->Evaluate(command);

    if (ret == -1) {
      break;
    }
    else if (ret == 0) {
      std::cout << "An invalid command was entered!" << std::endl;
    }
  }

  delete commandInterpreter;
  delete dvblinkRemoteCommunication;
  delete httpClient;

  return 0;
}
