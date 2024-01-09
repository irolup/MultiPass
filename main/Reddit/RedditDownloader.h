//
// Created by charlie on 09/01/24.
//
#include <string>
#include <nlohmann/json.hpp>

#ifndef MULTIPASS_REDDITDOWNLOADER_H
#define MULTIPASS_REDDITDOWNLOADER_H


class RedditDownloader {
public:
    RedditDownloader();
    ~RedditDownloader();
    void download_image(const std::string& url, const std::string& filepath);
    nlohmann::json get_json(const std::string& url);
private :
    static size_t write_data(void* ptr, size_t size, size_t nmemb, std::string* data);
};


#endif //MULTIPASS_REDDITDOWNLOADER_H
