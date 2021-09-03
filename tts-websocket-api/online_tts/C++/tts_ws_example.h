#ifndef __WSTTS_EXAMPLE_H__
#define __WSTTS_EXAMPLE_H__


#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <string>
#include <list>
#include <boost/thread.hpp>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
typedef client::connection_ptr connection_ptr;


struct tts_params
{
    /*����  �ϳɵ��ı���ʹ��UTF-8���룬���Ȳ�����1024�ֽڣ��������base64����*/
    std::string text;
    /*���� Ӧ�����������絼�����ͷ��ȣ������ֽ��б��룬Ŀǰֵ�̶�Ϊ1*/
    std::string domain;
    /* ����
    * �ϳ������ı�������
      ZH(���ĺ���Ӣ��)
      ENG(��Ӣ�ģ����Ĳ��ֲ���ϳ�)
      CAT(���
      SCH(�Ĵ���)
    */
    std::string language;
    /* �Ǳ���
    * ���ò��ŵ����٣���0��9֮�䣨֧�ָ���ֵ����Ĭ��ֵΪ5
    */
    std::string speed;
    /* �Ǳ���
    * ������������������0��9֮�䣨ֻ֧������ֵ����Ĭ��ֵΪ5
    */
    std::string volume;
    /* �Ǳ���
    * ������������������0��9֮�䣬��֧�ָ���ֵ����Ĭ��ֵΪ5
    */
    std::string pitch;
    /* �Ǳ���
    * ��Ƶ���ࣺ
        audiotype = 4������16K�����ʵ�pcm��ʽ��Ĭ��ֵ
        audiotype = 5������8K�����ʵ�pcm��ʽ
    */
    std::string audiotype;
    /* ����
    * ������ѡ���硰Jiaojiao", ��� �������б�
    */
    std::string voice_name;
    /* �Ǳ���
    * ��ƵƵ�ף�ȡֵ��Χ1~20�� Ĭ��ֵΪ1��������Ƶ�ף�
        1��������Ƶ�ף�
        1���ϵ�ֵ�����Ƶ�������ӷ��ȣ� ֵԽ�������ĸ�Ƶ������ǿԽ�࣬�����������ͼ�ϸ
    */
    std::string spectrum;
    /* �Ǳ���
    * ��Ƶ����Ƶ�ף�ȡֵ��Χ0~20��Ĭ��ֵΪ0�������8K��ƵƵ�׵ĵ����� �����ʽֻ�����¼��֣�
        audiotype=5&spectrum_8k=xx
        audiotype=6&rate=1&spectrum_8k=xx
        audiotype=7&spectrum_8k=xx
        audiotype=8&spectrum_8k=xx
    */
    std::string spectrum_8k;
    /* �Ǳ���
    * ȡֵ0/1��interval=1ʱ��������ʱ�����Ϣ
    */
    std::string interval;
    tts_params()
    {
        domain = "1";
        speed = "5";
        volume = "5";
        pitch = "5";
        audiotype = "4";
        spectrum = "1";
        spectrum_8k = "0";
    }
};

class tts_ws_example
{
public:
    static std::string get_token(const std::string& client_id, const std::string& client_secret);
    static std::string gen_json_request(const std::string& token, const std::string& version, const tts_params& params);
public:
    tts_ws_example(const std::list<std::string>& json_data_list);
    virtual ~tts_ws_example();
    bool open_connection(const std::string& uri);
    void send_request_frame(websocketpp::connection_hdl hdl, const std::string& data);
    void stop_io_service();
    void close_connection();
protected:
    context_ptr on_tls_init(websocketpp::connection_hdl);
    void on_open(websocketpp::connection_hdl hdl);
    void on_close(websocketpp::connection_hdl hdl);
    void on_fail(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
    void work_thread();
    void recv_audio_frame(const std::string& msg);
    void close_output_file();
private:
    client                              ws_client_;
    websocketpp::connection_hdl         hdl_;
    boost::mutex                        hdl_mutex_;
    boost::thread*                      work_thread_;
    std::list<std::string>              json_data_list_;
    FILE*                               output_file_;
    std::string                         output_filename_;
};

#endif // __WSTTS_EXAMPLE_H__
