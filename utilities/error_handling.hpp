#pragma once
#include <string>
#include <stdio.h>

class error {
public:
    error(std::string name, std::string details = "") {
        if (details == "")
            printf("[ERROR] %s\n", name.c_str());
        else
            printf("[ERROR] %s: %s\n", name.c_str(), details.c_str());

        printf("[ANNOUNCEMENT] halting due to error\n");
        exit(0);
    }
};