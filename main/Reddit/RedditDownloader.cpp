//
// Created by charlie on 09/01/24.
//

#include "RedditDownloader.h"
#include <curl/curl.h>
#include <fstream>

RedditDownloader::RedditDownloader(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
RedditDownloader::~RedditDownloader(){
    curl_global_cleanup();
}

static size_t write_data(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void download_image(const std::string& url, const std::string& filepath){
    CURL* curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();
    if(curl){
        fp = fopen(filepath.c_str(),"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

nlohmann::json get_json(const std::string& url){
    CURL* curl;
    std::string readBuffer;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return nlohmann::json::parse(readBuffer);
}