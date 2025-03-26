#include <iostream>
#include <cstring>

using namespace std;

struct File
{
    char* name;
    char* content;
    double fileSize;
};

struct HDD
{
    File** file;
    int fileCount;
    double maxSize;
    double size;
};

double FileSizeF(const char* size)
{
    return strlen(size);
}

int FileExists(HDD& hdd, const char* name)
{
    for (int i = 0; i < hdd.fileCount; i++)
    {
        if (strcmp(hdd.file[i]->name, name) == 0)
        {
            return i;
        }
    }

    return -1;
}

void CreatNewFile(HDD& hdd, const char* name, const char* content)
{
    if (FileExists(hdd, name) != -1)
    {
        cout << "\n\n";
        cout << "A file with this name already exists !";
        cout << "\n\n";

        return;
    }

    double NewSize = FileSizeF(content);

    if (hdd.size + NewSize > hdd.maxSize)
    {
        cout << "\n\n";
        cout << "Out of memory ! File not created !";
        cout << "\n\n";

        return;
    }

    File* new_file = new File;

    new_file->name = new char[strlen(name) + 1];

    for (int i = 0; name[i] != '\0'; ++i)
    {
        new_file->name[i] = name[i];
    }

    new_file->name[strlen(name)] = '\0';

    new_file->content = new char[strlen(content) + 1];

    for (int i = 0; content[i] != '\0'; ++i)
    {
        new_file->content[i] = content[i];
    }

    new_file->content[strlen(content)] = '\0';

    new_file->fileSize = NewSize;

    File** NewFile = new File * [hdd.fileCount + 1];

    for (int i = 0; i < hdd.fileCount; i++)
    {
        NewFile[i] = hdd.file[i];
    }

    NewFile[hdd.fileCount] = new_file;

    delete[] hdd.file;
    hdd.file = NewFile;

    hdd.fileCount++;
    hdd.size += NewSize;

    cout << "\n\n";
    cout << "File created successfully !";
    cout << "\n\n";
}

void UpdateFile(HDD& hdd, const char* name, const char* new_content)
{
    int index = FileExists(hdd, name);

    if (index == -1)
    {
        cout << "\n\n";
        cout << "-------------------------------";
        cout << "\n";
        cout << "files not found !";
        cout << "\n";
        cout << "-------------------------------";
        cout << "\n\n";
        return;
    }

    double oldSize = hdd.file[index]->fileSize;
    double newSize = FileSizeF(new_content);

    if (hdd.size - oldSize + newSize > hdd.maxSize)
    {
        cout << "\n\n";
        cout << "Memory is low ! Update failed !";
        cout << "\n\n";

        return;
    }

    delete[] hdd.file[index]->content;

    hdd.file[index]->content = new char[strlen(new_content) + 1];
    for (int i = 0; new_content[i] != '\0'; ++i)
    {
        hdd.file[index]->content[i] = new_content[i];
    }
    hdd.file[index]->content[strlen(new_content)] = '\0'; 

    hdd.file[index]->fileSize = newSize;

    hdd.size = hdd.size - oldSize + newSize;

    cout << "\n\n";
    cout << "File updated successfully !";
    cout << "\n\n";
}

void DeleteFile(HDD& hdd, const char* name)
{
    int index = FileExists(hdd, name);

    if (index == -1)
    {
        cout << "\n\n";
        cout << "-------------------------------";
        cout << "\n";
        cout << "files not found !";
        cout << "\n";
        cout << "-------------------------------";
        cout << "\n\n";

        return;
    }

    hdd.size -= hdd.file[index]->fileSize;

    delete[] hdd.file[index]->name;
    delete[] hdd.file[index]->content;
    delete hdd.file[index];

    File** NewSize = nullptr;

    if (hdd.fileCount - 1 > 0)
    {
        NewSize = new File * [hdd.fileCount - 1];
        int NewIndex = 0;

        for (int i = 0; i < hdd.fileCount; i++)
        {
            if (i != index)
            {
                NewSize[NewIndex++] = hdd.file[i];
            }
        }
    }

    delete[] hdd.file;

    hdd.file = NewSize;
    hdd.fileCount--;

    cout << "\n\n";
    cout << "File deleted successfully !";
    cout << "\n\n";
}

void Show(HDD& hdd)
{
    if (hdd.fileCount == 0)
    {
        cout << "\n\n";
        cout << "-------------------------------";
        cout << "\n";
        cout << "files not found !";
        cout << "\n";
        cout << "-------------------------------";
        return;
    }

    for (int i = 0; i < hdd.fileCount; i++)
    {
        cout << hdd.file[i]->name << " (" << hdd.file[i]->fileSize << " bayt)" << endl;
        cout << " - " << "[ " << hdd.file[i]->content << " ]" << endl;
    }

    cout << "\n\n";
    cout << "Total Memory Used : " << hdd.size << " / " << hdd.maxSize << " bayt" << endl;
    cout << "\n\n";
}

void Clean(HDD& hdd)
{
    for (int i = 0; i < hdd.size; i++)
    {
        delete[] hdd.file[i]->name;
        delete[] hdd.file[i]->content;
        delete hdd.file[i];
    }

    delete[] hdd.file;
    hdd.file = nullptr;

    hdd.size = 0;
    hdd.fileCount = 0;
}

int main()
{
    cout << "----------------------------";
    cout << "\n\n";
    cout << "Tap - 1";
    cout << "\n\n";

    //struct User 
    //{
    //	char* name;
    //	__int8 age;
    //	__int8 score;
    //};
    // 
    //int main()
    //{
    //
    //	User michel = { new char [20] { "bob" }, 12, 7 };
    //}

    //----------------------Izah------------------------
    // Mende kod isleyir

    cout << "\n\n";
    cout << "----------------------------";
    cout << "\n\n";
    cout << "Tap - 2";
    cout << "\n\n";

    HDD hdd;
    hdd.file = nullptr;
    hdd.size = 0;
    hdd.maxSize = 1024;
    hdd.fileCount = 0;

    int choice;
    char file_name[100];
    char content[1000];

    while (true)
    {
        cout << "\n\n";

        cout << "Add new file    | 1" << endl;
        cout << "Update file     | 2" << endl;
        cout << "Delete file     | 3" << endl;
        cout << "Show file       | 4" << endl;
        cout << "Exit            | 5" << endl;

        cout << "\n\n";

        cout << "Enter choice : ";
        cin >> choice;

        cout << "\n\n";

        cin.ignore(); 

        switch (choice)
        {
        case 1:
            cout << "-----------------------------";
            cout << "\n\n";

            cout << "Enter  file name : ";
            cin.getline(file_name, 100);

            cout << "\n";

            cout << "Enter content : ";
            cin.getline(content, 1000);

            CreatNewFile(hdd, file_name, content);
            break;

        case 2:
            cout << "-----------------------------";
            cout << "\n\n";

            cout << "Enter  file name for update : ";
            cin.getline(file_name, 100);

            cout << "\n";

            cout << "Enter content for update : ";
            cin.getline(content, 1000);

            UpdateFile(hdd, file_name, content);
            break;

        case 3:
            cout << "-----------------------------";
            cout << "\n\n";

            cout << "Enter  file name for delete : ";
            cin.getline(file_name, 100);

            DeleteFile(hdd, file_name);
            break;

        case 4:
            cout << "-----------------------------";
            cout << "\n\n";

            Show(hdd);
            break;

        case 5:
            cout << "-----------------------------";
            cout << "\n\n";

            cout << "Exit system .... ";
            exit(0);
            break;

        default:
            cout << "-----------------------------";
            cout << "\n\n";

            cout << "Error ! False choice!";
            break;
        }
    }
}
