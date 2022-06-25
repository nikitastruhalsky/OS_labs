#include <iostream>
#include <unistd.h>

std::string paths[] = {"../../A/cmake-build-debug/A",
                       "../../M/cmake-build-debug/M",
                       "../../P/cmake-build-debug/P",
                       "../../S/cmake-build-debug/S"};


int main()
{
    int pfd[2];
    std::cout << "Insert" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        pipe(pfd);
        if (fork() == 0)
        {
            dup2(pfd[1], 1);
            std::system(paths[i].c_str());
            std::exit(0);
        }

        dup2(pfd[0], 0);
        close(pfd[1]);
    }

    std::system(paths[3].c_str());
    return 0;
}
