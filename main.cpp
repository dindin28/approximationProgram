#include <stdio.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#ifdef __linux__
    #include <unistd.h>
    #include <termios.h>
    int getch()
    {
        int ch;
        struct termios oldt, newt;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
    }
    #define system(A); system("clear");
#elif _WIN32
    #include <conio.h>
    #define system(A); system("cls");
#else

#endif
void fillSpace(double number);
void showMatrix(std::vector<double> arrayBuff){
    if(arrayBuff.size() != 0){
        printf("|1't coor|2'd coor| index\n");
        printf("|--------|--------|\n");
        for(int i = 0; i < arrayBuff.size(); i += 2){
            printf("|");
            fillSpace(arrayBuff[i]);
            printf("%.3lf", arrayBuff[i]);
            printf("|");
            fillSpace(arrayBuff[i + 1]);
            printf("%.3lf", arrayBuff[i + 1]);
            printf("| %i\n", i / 2 + 1);
            printf("|--------|--------|\n");
        }
    }
}
void fillSpace(double number){
    if(fabs(number) >= 0 && fabs(number) < 10){
        printf("   ");
    }else if(fabs(number) >= 10 && fabs(number) < 100){
        printf("  ");
    }else if(fabs(number) >= 100 && fabs(number) < 1000){
        printf(" ");
    }
}
int main()
{
    std::vector<double> array;
    int key;
    do{
        system("cls");
        showMatrix(array);
        printf("1 - Edit plot\n2 - Write plot\n3 - Generate code\n0 - Exit\nEnter number: ");
        scanf("%i", &key);
        switch (key){
            case(1):{
                do{
                    system("cls");
                    if(array.size() != 0){
                        showMatrix(array);
                    }
                    printf("1 - Add new coordinate\n2 - Add coordinate at index\n3 - Erase last coordinate\n4 - Erase coordinate at index\n0 - Exit\nEnter number: ");
                    scanf("%i", &key);
                    switch(key){
                        case(1):{
                            double x;
                            double y;
                            printf("Limit for coordinates is 9999\n");
                            printf("Enter 1'st coordinate: ");
                            std::cin.ignore(32767, '\n');
                            scanf("%lf", &x);
                            printf("Enter 2'st coordinate: ");
                            std::cin.ignore(32767, '\n');
                            scanf("%lf", &y);
                            if(x >= 0 && x < 10000 && y >= 0 && y < 10000){
                                array.push_back(x);
                                array.push_back(y);
                            }else{
                                printf("Out of diapason\n");
                                printf("Press any key");
                                std::cin.ignore(32767, '\n');
                                getch();
                            }
                            break;
                        }
                        case(2):{
                            int index = 0;
                            printf("Enter index to add: ");
                            std::cin.ignore(32767, '\n');
                            scanf("%i", &index);
                            if(index <= ((array.size() / 2) + 1)){
                                printf("Limit for coordinates is 9999\n");
                                index = (index - 1) * 2;
                                double x;
                                double y;
                                printf("Enter 1'st coordinate: ");
                                std::cin.ignore(32767, '\n');
                                scanf("%lf", &x);
                                printf("Enter 2'st coordinate: ");
                                std::cin.ignore(32767, '\n');
                                scanf("%lf", &y);
                                if(x >= 0 && x < 10000 && y >= 0 && y < 10000){
                                    array.insert(array.begin() + index, x);
                                    array.insert(array.begin() + index + 1, y);
                                }else{
                                    printf("Out of diapason\n");
                                    printf("Press any key");
                                    std::cin.ignore(32767, '\n');
                                    getch();
                                }
                            }else{
                                printf("It's impossible!\n");
                                printf("Press any key");
                                std::cin.ignore(32767, '\n');
                                getchar();
                            }
                            break;
                        }
                        case(3):{
                            if(array.size() != 0){
                                array.pop_back();
                                array.pop_back();
                            }else{
                                printf("There are no elements in matrix\n");
                                printf("Press any key");
                                std::cin.ignore(32767, '\n');
                                getchar();
                            }
                            break;
                        }
                        case(4):{
                            if(array.size() != 0){
                                int index = 0;
                                printf("Enter index to delete: ");
                                std::cin.ignore(32767, '\n');
                                scanf("%i", &index);
                                index = (index - 1) * 2;
                                array.erase(array.begin() + index);
                                array.erase(array.begin() + index);
                                printf("\n");
                            }else{
                                printf("There are no elements in matrix\n");
                                printf("Press any key");
                                std::cin.ignore(32767, '\n');
                                getchar();
                            }
                            break;
                        }
                        case(0):{
                            break;
                        }
                        default: {
                            printf("Enter another value\n");
                            printf("Press any key");
                            std::cin.ignore(32767, '\n');
                            getch();
                        }
                    }
                }while(key != 0);
                key = 1;
                break;
            }
            case(2):{
                if(array.size() != 0){
                    time_t curr_time;
                    time(&curr_time);
                    std::string str = asctime(localtime(&curr_time));
                    for(int i = 0; i < str.length(); i++){
                        if(str[i] == ':')
                            str.replace(str.begin() + i, str.begin() + i + 1, "-");
                        if(str[i] == ' ')
                            str.replace(str.begin() + i, str.begin() + i + 1, "_");
                    }
                    str.pop_back();
                    std::ofstream fout(str + "_points.txt");
                    for(int i = 0; i < array.size(); i++){
                        if(i % 2 == 0 && i != 0){
                            fout << "\n";
                        }
                        fout << array[i] << " ";
                    }
                    fout.close();
                    printf("Array is written successfully\n");
                }else printf("Array is empty!!!\n");
                std::cin.ignore(32767, '\n');
                printf("Press any key");
                getchar();
                break;
            }
            case(3):{
                if(array.size() >= 4){
                    showMatrix(array);
                    time_t curr_time;
                    time(&curr_time);
                    std::string str = asctime(localtime(&curr_time));
                    for(int i = 0; i < str.length(); i++){
                        if(str[i] == ':')
                            str.replace(str.begin() + i, str.begin() + i + 1, "-");
                        if(str[i] == ' ')
                            str.replace(str.begin() + i, str.begin() + i + 1, "_");
                    }
                    str.pop_back();
                    std::ofstream fout(str + "_equations.txt");
                    for(int i = 0; i < array.size() - 2; i += 2){
                        std::cout << "y = " << (array[i + 3] - array [i + 1]) / (array[i + 2] - array[i]) << "x - " <<
                        (array[i + 1] * (array[i + 2] - array[i]) - array[i] * (array[i + 3] - array[i + 1])) / (array[i + 2] - array[i]);
                        std::cout << "\n";
                        fout << "y = " << (array[i + 3] - array [i + 1]) / (array[i + 2] - array[i]) << "x - " <<
                        (array[i + 1] * (array[i + 2] - array[i]) - array[i] * (array[i + 3] - array[i + 1])) / (array[i + 2] - array[i]);
                        fout << "\n";
                    }
                }else printf("Array is empty!!!\n");
                std::cin.ignore(32767, '\n');
                printf("Press any key");
                getchar();
                break;
            }
        }
    }while(key != 0);
    return 0;
}
