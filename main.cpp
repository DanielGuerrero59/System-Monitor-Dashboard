#define _WIN32_WINNT 0x0601 // tells our c++ compiler to to use features introduced in windows 7 or higher 
#include "crow.h"   // framework to allow C++ to be used as a web server
#include <windows.h>  // OPERATING SYSTEM API, 
#include <cmath>



    int main()
    {
        // Creates the instance app from the SimpleApp class within the crow framework, SimpleAPP is the engine of our entire web server 
        crow::SimpleApp app; 


        // looks into our templates folder and loads whats inside as the homepage
        CROW_ROUTE(app, "/")([]() {
            // This looks into the 'templates' folder automatically
            auto page = crow::mustache::load("index.html");
            return page.render();
            });
       



        //SECOND ROUTE 
        CROW_ROUTE(app, "/ram")([]() {
            //Create folder for the data 
            MEMORYSTATUSEX statex; // MEMORYSTATUSEX is a struct that gives us an entire slot of data on ram into this keyword, being stored in our folder statex. 
            statex.dwLength = sizeof(statex); // size of measures how big this folder is in bytes, and it is stores this in .dwLength

            GlobalMemoryStatusEx(&statex);  // this line is the actual request to WINDOWS OS, and we send it the address of our folder 

            int load = statex.dwMemoryLoad; // we take the percentage of the ram and put it in our variable load 

            // Create a JSON Object 
            crow::json::wvalue response; 

            // assign values into the object 
            response["percent_used"] = statex.dwMemoryLoad; 
            double raw_gb = statex.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
            double total_gb = std::round(raw_gb * 100 + 0.5) / 100;
            response["total_gb"] = total_gb; 
            return response; 


        });
        app.port(8080).run(); // door for the users request to come into the data 
        return 0; 
    }