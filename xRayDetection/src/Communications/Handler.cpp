#include "Communications/Handler.h"

#include "External/Civet/Civetweb.h"
#include "Common/Logger.hpp"

namespace Communications
{
    bool Handler::handleGet(CivetServer* server, struct mg_connection* conn)
    {
        conn_ = conn;
        
        return handle();
    }

    std::string Handler::getRequestHeader(const std::string& name)
    {
        const mg_request_info* resInfo =  mg_get_request_info(conn_);
        int numHeaders = resInfo->num_headers;
        const auto& headers = resInfo->http_headers;
        
        return getHeader(headers, numHeaders, name);
    }

    

    std::string Handler::getResponseHeader(const std::string& name)
    {
        const mg_response_info* resInfo =  mg_get_response_info(conn_);
        int numHeaders = resInfo->num_headers;
        const auto& headers = resInfo->http_headers;

        return getHeader(headers, numHeaders, name);
    }
    
    void Handler::sendJson(mg_connection *conn, const std::string& jsonData, 
            const std::vector<mg_header>& optionalHeaders)
    {
        mg_response_header_start(conn, 200);
        mg_response_header_add(conn, "Access-Control-Allow-Origin", "*", -1);
        mg_response_header_add(conn, "Content-Type", "application/json", -1);
        for(const auto& header: optionalHeaders)
            mg_response_header_add(conn, header.name, header.value, -1);
            
        mg_response_header_send(conn);

        mg_printf(conn, "%s", jsonData.c_str());
    }



    void Handler::sendOK(mg_connection *conn)
    {
        mg_response_header_start(conn, 200);
        mg_response_header_add(conn, "Access-Control-Allow-Origin", "*", -1);
        mg_response_header_add(conn, "Content-Type", "application/text", -1);
        mg_response_header_send(conn);
    }

    void Handler::sendErr(mg_connection *conn, int code)
    {
        mg_response_header_start(conn, 200);
        mg_response_header_add(conn, "Access-Control-Allow-Origin", "*", -1);
        mg_response_header_send(conn);
    }


    void Handler::sendFile(mg_connection *conn, const std::string& path)
    {
        mg_send_file(conn, path.c_str());
    }

    std::string Handler::getHeader(const mg_header *headers, int numHeaders, const std::string& name)
    {
        std::string value;

        for(int idx = 0; idx < numHeaders; ++idx)
        {
            if(name == headers[idx].name)
            {
                value = headers[idx].value;
                break;
            }
        }
        return value;
    }
}