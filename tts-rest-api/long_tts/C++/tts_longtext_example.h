#ifndef __TTS_LONGTEXT_EXAMPLE_H__
#define __TTS_LONGTEXT_EXAMPLE_H__

#include <string>

struct request_params
{
    /* ����
    * ͨ��client_id��client_secret������Ȩ�����ü���ȡ��������
    */
    std::string  access_token;
    /* ����
    * ��Ҫ�ϳɵ��ı���ע�⻻�з���url���룩֧��һ�����ϴ�������10����ֽ�
    */
    std::string  text;
    /* ����
    * ���÷������������ƣ���� �������б�
    */
    std::string  voice_name;
    /* ����
    * �õ�ַ���ڽ��պϳɽ�����õ�ַ����Ϊ�����ɷ��ʵ�url������Я������
    */
    std::string  notify_url;
    /* �Ǳ���
    * �Ƿ�Я��interval��Ϣ��
        0����Я����Ĭ��ֵ
        1��Я��
    */
    int          interval;
    /* �Ǳ���
    * ���ò��ŵ����٣���0��9֮�䣨֧��һλ����ֵ��������ʱĬ��Ϊ5
    */
    std::string  speed;
    /* �Ǳ���
    * ������������������0��9֮�䣨ֻ֧������ֵ��������ʱ Ĭ��ֵΪ5
    */
    std::string  volume;
    /* �Ǳ���
    * �ɲ���
    audiotype=3 ������mp3��ʽ
    audiotype=4 ������16K�����ʵ�pcm��ʽ
    audiotype=6 ������16K�����ʵ�wav��ʽ
    */
    int          audiotype;
    request_params()
    {
        interval = 0;
        speed = "5";
        volume = "5";
        audiotype = 0;
    }
};

class tts_longtext_example
{
public:
    static std::string get_token(const std::string& client_id, const std::string& client_secret);
    static std::string gen_json_request(const request_params& req_params);
public:
    tts_longtext_example(const std::string& long_text_url);
    ~tts_longtext_example();
    bool send_request(const request_params& req_params);
protected:
    std::string long_text_url_;
};

#endif // __TTS_LONGTEXT_EXAMPLE_H__
