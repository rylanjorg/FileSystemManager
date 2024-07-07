#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;
namespace fs = std::filesystem;

void create_directory();
void rename_directory();
void delete_directory();
void create_file();
void rename_file();
void edit_file();
void delete_file();
void generate_random_data();
void move_file();
void duplicate_file();
void duplicate_directory();
void search_file();
void display_directory();
void get_basic_file_info();
void get_detailed_file_info();
void get_basic_directory_info();
void get_detailed_directory_info();

int main() {
    int choice;

    do {
        // Display menu
        cout << "1. Create directory\n";
        cout << "2. Rename directory\n";
        cout << "3. Delete directory\n";
        cout << "4. Create file\n";
        cout << "5. Rename file\n";
        cout << "6. Edit file\n";
        cout << "7. Delete file\n";
        cout << "8. Generate random data\n";
        cout << "9. Move file\n";
        cout << "10. Duplicate file\n";
        cout << "11. Duplicate directory\n";
        cout << "12. Search file\n";
        cout << "13. Display directory\n";
        cout << "14. Get basic file info\n";
        cout << "15. Get detailed file info\n";
        cout << "16. Get basic directory info\n";
        cout << "17. Get detailed directory info\n";
        cout << "18. Exit\n";

        // Get user choice
        cout << "Enter your choice: ";
        cin >> choice;

        // Execute selected function
        switch (choice) {
            case 1:
                create_directory();
                break;
            case 2:
                rename_directory();
                break;
            case 3:
                delete_directory();
                break;
            case 4:
                create_file();
                break;
            case 5:
                rename_file();
                break;
            case 6:
                edit_file();
                break;
            case 7:
                delete_file();
                break;
            case 8:
                generate_random_data();
                break;
            case 9:
                move_file();
                break;
            case 10:
                duplicate_file();
                break;
            case 11:
                duplicate_directory();
                break;
            case 12:
                search_file();
                break;
            case 13:
                display_directory();
                break;
            case 14:
                get_basic_file_info();
                break;
            case 15:
                get_detailed_file_info();
                break;
            case 16:
                get_basic_directory_info();
                break;
            case 17:
                get_detailed_directory_info();
                break;
            case 18:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 18);

    return 0;
}

// Define the functions

void create_directory() {
    std::string dirname;
    std::cout << "Enter directory name: ";
    std::cin >> dirname;
    int status = mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status == 0) {
        std::cout << "Directory created successfully." << std::endl;
    } else {
        std::cerr << "Error creating directory." << std::endl;
    }
}

void rename_directory() {
    std::string oldname, newname;
    std::cout << "Enter old directory name: ";
    std::cin >> oldname;
    std::cout << "Enter new directory name: ";
    std::cin >> newname;
    int status = rename(oldname.c_str(), newname.c_str());
    if (status == 0) {
        std::cout << "Directory renamed successfully." << std::endl;
    } else {
        std::cerr << "Error renaming directory." << std::endl;
    }
}

void delete_directory() {
    std::string dirname;
    std::cout << "Enter directory name: ";
    std::cin >> dirname;
    DIR* dir = opendir(dirname.c_str());
    if (dir == NULL) {
        std::cerr << "Error opening directory." << std::endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string path = dirname + "/" + entry->d_name;
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            delete_directory(path);
        } else {
            remove(path.c_str());
        }
    }
    closedir(dir);
    int status = rmdir(dirname.c_str());
    if (status == 0) {
        std::cout << "Directory deleted successfully." << std::endl;
    } else {
        std::cerr << "Error deleting directory." << std::endl;
    }
}

void create_file() {
    std::string filename;
    std::cout << "Enter the name of the file to create: ";
    std::getline(std::cin, filename);

    int num_bytes;
    std::cout << "Enter the number of bytes to generate: ";
    std::cin >> num_bytes;

    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: could not create file.\n";
        return;
    }

    char* buffer = new char[num_bytes];
    for (int i = 0; i < num_bytes; i++) {
        buffer[i] = rand() % 256;
    }

    file.write(buffer, num_bytes);
    file.close();
    delete[] buffer;

    std::cout << "File created successfully.\n";
}

void rename_file() {
    string oldname, newname;
    cout << "Enter the name of the file you want to rename: ";
    cin >> oldname;
    cout << "Enter the new name for the file: ";
    cin >> newname;
    if (rename(oldname.c_str(), newname.c_str()) != 0) {
        cerr << "Error renaming file." << endl;
    } else {
        cout << "File renamed successfully." << endl;
    }
}

void edit_file() {
    string filename;
    cout << "Enter the name of the file you want to edit: ";
    cin >> filename;
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    cout << "Enter the text you want to write to the file (press Ctrl-D to finish):" << endl;
    string line;
    while (getline(cin, line)) {
        file << line << endl;
    }
    file.close();
    cout << "File edited successfully." << endl;
}

void delete_file() {
    string filename;
    cout << "Enter the name of the file you want to delete: ";
    cin >> filename;
    if (remove(filename.c_str()) != 0) {
        cerr << "Error deleting file." << endl;
    } else {
        cout << "File deleted successfully." << endl;
    }
}

void generate_random_data() {
    string filename;
    int size;
    cout << "Enter the name of the file you want to generate random data for: ";
    cin >> filename;
    cout << "Enter the size of the file (in bytes): ";
    cin >> size;
    ofstream file(filename.c_str(), ios::out | ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        char byte = rand() % 256;
        file.write(&byte, sizeof(byte));
    }
    file.close();
    cout << "Random data generated and written to file successfully." << endl;
}

void move_file() {
    string oldname, newname;
    cout << "Enter the name of the file you want to move: ";
    cin >> oldname;
    cout << "Enter the name of the directory you want to move the file to: ";
    cin >> newname;
    if (rename(oldname.c_str(), (newname + "/" + oldname).c_str()) != 0) {
        cerr << "Error moving file." << endl;
    } else {
        cout << "File moved successfully." << endl;
    }
}


void duplicate_file() {
    std::string src_filename, dst_filename;
    std::cout << "Enter the name of the file to duplicate: ";
    std::cin >> src_filename;
    std::cout << "Enter the name of the new file: ";
    std::cin >> dst_filename;

    std::ifstream src_file(src_filename, std::ios::binary);
    if (!src_file.is_open()) {
        std::cerr << "Error opening source file." << std::endl;
        return;
    }

    std::ofstream dst_file(dst_filename, std::ios::binary);
    if (!dst_file.is_open()) {
        std::cerr << "Error opening destination file." << std::endl;
        return;
    }

    dst_file << src_file.rdbuf();

    src_file.close();
    dst_file.close();

    std::cout << "File duplicated successfully." << std::endl;
}


void duplicate_directory(string source_dir, string target_dir) {
    DIR* source = opendir(source_dir.c_str());
    if (source == NULL) {
        cerr << "Error opening source directory." << endl;
        return;
    }

    DIR* target = opendir(target_dir.c_str());
    if (target == NULL) {
        cerr << "Error opening target directory." << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(source)) != NULL) {
        string source_file_path = source_dir + "/" + entry->d_name;
        string target_file_path = target_dir + "/" + entry->d_name;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        struct stat s;
        lstat(source_file_path.c_str(), &s);

        if (S_ISDIR(s.st_mode)) {
            mkdir(target_file_path.c_str(), 0777);
            duplicate_directory(source_file_path, target_file_path);
        } else {
            ifstream source_file(source_file_path.c_str(), ios::binary);
            ofstream target_file(target_file_path.c_str(), ios::binary);

            target_file << source_file.rdbuf();

            source_file.close();
            target_file.close();
        }
    }

    closedir(source);
    closedir(target);

    cout << "Directory duplicated successfully." << endl;
}

void search_file() {
    std::string filename;
    std::cout << "Enter the name of the file to search for: ";
    std::getline(std::cin, filename);

    DIR* dir = opendir(".");
    if (dir == NULL) {
        std::cerr << "Error opening directory." << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string path = std::string(entry->d_name);
        if (path == "." || path == "..") {
            continue;
        }

        if (entry->d_type == DT_DIR) {
            chdir(entry->d_name);
            search_file();
            chdir("..");
        } else if (entry->d_type == DT_REG && path == filename) {
            std::cout << "File found: " << getcwd(NULL, 0) << "/" << filename << std::endl;
        }
    }
    closedir(dir);
}


void display_directory() {
    std::string dirname;
    std::cout << "Enter starting directory: ";
    std::cin >> dirname;
    display_directory(dirname, 0);
}

void display_directory(const std::string& dirname, int level) {
    DIR* dir = opendir(dirname.c_str());
    if (dir == NULL) {
        std::cerr << "Error opening directory: " << dirname << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            std::cout << std::string(level, '\t') << entry->d_name << "/" << std::endl;
            std::string path = dirname + "/" + entry->d_name;
            display_directory(path, level + 1);
        } else {
            std::cout << std::string(level, '\t') << entry->d_name << std::endl;
        }
    }

    closedir(dir);
}

void get_basic_file_info() {
    string filename;
    cout << "Enter the name of the file you want information about: ";
    cin >> filename;

    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == -1) {
        cerr << "Error: could not get file information.\n";
        return;
    }

    cout << "Information for " << filename << ":\n";
    cout << "Size: " << fileStat.st_size << " bytes\n";
    cout << "Owner UID: " << fileStat.st_uid << "\n";
    cout << "Last access time: " << ctime(&fileStat.st_atime);
}

void get_detailed_file_info() {
    std::string filename;
    std::cout << "Enter the name of the file you want to get information about: ";
    std::cin >> filename;

    struct stat file_stat;
    if (stat(filename.c_str(), &file_stat) == -1) {
        std::cerr << "Error: could not get file information.\n";
        return;
    }

    std::cout << "Information for file: " << filename << "\n";
    std::cout << "Size: " << file_stat.st_size << " bytes\n";
    std::cout << "Owner user ID: " << file_stat.st_uid << "\n";
    std::cout << "Owner group ID: " << file_stat.st_gid << "\n";
    std::cout << "Permissions: " << (file_stat.st_mode & 0777) << "\n";
    std::cout << "Last accessed: " << ctime(&file_stat.st_atime);
    std::cout << "Last modified: " << ctime(&file_stat.st_mtime);
    std::cout << "Last status change: " << ctime(&file_stat.st_ctime);
}

void get_basic_directory_info() {
    std::string dir_path;
    std::cout << "Enter directory path: ";
    std::getline(std::cin, dir_path);

    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
        std::cout << "Error: invalid directory path.\n";
        return;
    }

    std::cout << "Directory name: " << fs::path(dir_path).filename() << '\n';
    std::cout << "Number of files: " << std::distance(fs::directory_iterator(dir_path), fs::directory_iterator{}) << '\n';
    std::cout << "Size: " << fs::directory_entry(dir_path).file_size() << " bytes\n";
}


void get_detailed_directory_info() {
    std::filesystem::path current_dir = std::filesystem::current_path();
    std::cout << "Detailed information about directory: " << current_dir << "\n";
    std::cout << "---------------------------------------------\n";

    for (const auto& entry : std::filesystem::directory_iterator(current_dir)) {
        std::cout << std::left << std::setw(30) << entry.path().filename().string() << " "; // Name
        std::cout << std::left << std::setw(15) << std::filesystem::file_size(entry.path()) << " "; // Size
        std::cout << std::left << std::setw(30) << std::filesystem::last_write_time(entry.path()).time_since_epoch().count() << " "; // Last Modified Time
        std::cout << std::left << std::setw(10) << ((std::filesystem::is_directory(entry.status())) ? "Directory" : "File") << "\n"; // Type
    }
}










