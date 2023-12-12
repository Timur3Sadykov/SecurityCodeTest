#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <array>
#include <stdexcept>
#include <cassert>
#include "MD5.h"

using std::filesystem::path;

bool CheckFileIntegrity(const path& file_path, const path& hash_path)
{
    std::ifstream file_stream(file_path, std::ios::binary);
    if (!file_stream)
    {
        throw std::runtime_error("Can't open file");
    }

    std::ifstream hash_stream(hash_path, std::ios::binary);
    if (!hash_stream)
    {
        throw std::runtime_error("Can't open hash");
    }

    std::string ref_hash;
    hash_stream >> ref_hash;

    static const int BUFF_SIZE = 1024;
    std::array<char, BUFF_SIZE> buffer;
    MD5 md5_hash;

    do
    {
        file_stream.read(buffer.data(), BUFF_SIZE);
        md5_hash.update(buffer.data(), file_stream.gcount());
    }
    while (file_stream);

    return md5_hash.finalize().hexdigest() == ref_hash;
}

void TestCheckFileIntegrity()
{
    assert(CheckFileIntegrity(path{ DATA_DIR "test_file.jpg" }, path{ DATA_DIR "reference_hash.txt" }));
    assert(!CheckFileIntegrity(path{ DATA_DIR "test_file.jpg" }, path{ DATA_DIR "invalid_hash.txt" }));
}

int main()
{
    TestCheckFileIntegrity();

    path file_path, hash_path;
    std::cout << "Enter absolute file path:" << std::endl;
    std::cin >> file_path;
    std::cout << "Enter absolute hash path:" << std::endl;
    std::cin >> hash_path;

    if (CheckFileIntegrity(file_path, hash_path))
    {
        std::cout << "Integrity check successful" << std::endl;
    }
    else
    {
        std::cout << "Integrity check failed" << std::endl;
    }
}