#ifndef __ASR_RESTFULAPI_EXAMPLE_H__
#define __ASR_RESTFULAPI_EXAMPLE_H__

#include <string>
#include <list>

struct asr_params
{
    /* ����
    * ͨ��client_id��client_secret������Ȩ�����ü���ȡ��������
    */
    std::string  access_token;
    /* ����
    * ��Ƶ�����ʽ
      wav
      pcm
    */
    std::string audio_format;
    /* ����
    * ��Ƶ������
        8000
        16000
    */
    int sample_rate;
    /* �Ǳ���
    * ģ�����ƣ�ͨ��ģ�� "common"��
    Ӣ��ģ��"english"��
    Ĭ��ֵΪ��common��
    */
    std::string domain;
    /* �Ǳ���
    * true: �ӱ�㣬Ĭ��ֵ
      false������ӱ��
    */
    std::string add_pct;
    asr_params()
    {
        domain = "common";
        add_pct = "true";
    }
};

class asr_restfulapi_example
{
public:
    static std::string get_token(const std::string& client_id, const std::string& client_secret);
    static std::list<std::string> gen_request_header(const asr_params& req_params);
    static bool read_file(const std::string& filename, std::string& data);
public:
    asr_restfulapi_example(const std::string& url);
    ~asr_restfulapi_example();
    bool send_request(const std::string& filename, const asr_params& req_params);
protected:
    std::string url_;
};

#endif // __ASR_RESTFULAPI_EXAMPLE_H__
