#pragma once


enum class MessageType: unsigned int{
    MSG_INVALID = 0,    
    MSG_INIT,
    MSG_EXIT,
    MSG_SNED_PIC,        // new picture send
    MSG_RESEND_PIC      
};


struct MsgHdr
{
    MessageType     type;
    unsigned int    msgSize;
};

struct MsgInit: MsgHdr
{
    
};


struct MsgExit: MsgHdr
{
    /* data */
};


struct MsgSendFileHdr: MsgHdr
{
    unsigned char   fileName[64];   // 名字包括后缀
    unsigned int    fileNameSize;   // 名字长度， 保留
    unsigned int    fileSize;       // 数据大小
    unsigned char   hash[16];       // 默认采用md5校验这个数据的完整性
};


struct MsgSendPic: MsgSendFileHdr
{
    // TODO: 若发送图片有其他需要增加的可以加在此处
};

// 重发只需要把这个MsgHdr的type 改为 resend 由 client 发送到服务器即可
struct MsgResendPic: MsgSendFileHdr
{

};





