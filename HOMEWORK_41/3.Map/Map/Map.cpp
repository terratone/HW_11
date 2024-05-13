#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::map<std::string, int> wordFrequency; // Создаем map для хранения частот слов

    std::ifstream file("input.txt"); // Открываем файл с исходным текстом
    if (!file.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    std::string word;
    while (file >> word) {
        // Удаляем пунктуацию с конца слова
        while (!isalpha(word.back())) {
            word.pop_back();
        }

        // Преобразуем слово в нижний регистр
        for (char& c : word) {
            c = tolower(c);
        }

        // Увеличиваем частоту данного слова
        wordFrequency[word]++;
    }
    file.close();

    // Вывод информации о всех словах
    for (const auto& pair : wordFrequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Находим наиболее часто встречающееся слово
    std::string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& pair : wordFrequency) {
        if (pair.second > maxFrequency) {
            mostFrequentWord = pair.first;
            maxFrequency = pair.second;
        }
    }

    if (!mostFrequentWord.empty()) {
        std::cout << "Most frequent word: " << mostFrequentWord << " (" << maxFrequency << " occurrences)" << std::endl;
    }

    // Записываем результаты в файл
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the output file." << std::endl;
        return 1;
    }

    for (const auto& pair : wordFrequency) {
        outputFile << pair.first << ": " << pair.second << std::endl;
    }

    outputFile.close();

    return 0;
}