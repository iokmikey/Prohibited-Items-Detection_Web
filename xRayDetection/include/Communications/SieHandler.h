#pragma once
#include "External/Civet/CivetServer.h"
#include "External/Civet/Civetweb.h"

#include "Communications/Handler.h"

namespace Communications
{
    // 用于处理来自 安检机的 数据 (security inspection machine)
    class SieHandler: public Handler
    {
    public:
        //bool handleGet(CivetServer* server, struct mg_connection* conn) override;
    };
} // namespace Communications
