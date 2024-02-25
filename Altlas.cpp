#include <iostream>
#include <curl/curl.h>
#include <locale.h>

using namespace std;

// Функция обратного вызова для записи данных из запроса в строку
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("chcp");
    CURL* curl;
    CURLcode res;
    string url = "your_URL"; // Замените на соответствующий URL API

    // Инициализация библиотеки cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        // Установка URL-адреса и других параметров запроса
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Если требуется аутентификация по логину и паролю, установите их здесь
        curl_easy_setopt(curl, CURLOPT_USERNAME, "your_login");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "your_password");

        // Устанавливаем функцию обратного вызова для записи данных
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Выполнение запроса
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << "Schedule response: " << response_string << std::endl;

        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Error 0231: Failed to initialize cURL" << std::endl;
    }

    // Освобождение глобальных ресурсов
    curl_global_cleanup();
    return 0;
}
