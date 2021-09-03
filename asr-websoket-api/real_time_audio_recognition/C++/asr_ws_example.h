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


struct asr_params
{
    /*����  ԭʼ��Ƶÿ���̶�5120�ֽڣ����һ������, ����ʹ��base64���б���*/
    std::string audio_data;
    /*���� 
    * ��Ƶ�����ʽ
        pcm
        wav
    */
    std::string audio_format;
    /* ����
    * ��Ƶ������
        8000
        16000
    */
    int sample_rate;
    /* ����
    * ��Ƶ�������������Ϊ1���� 0����ʼ��Ƶ֡ >0���м���Ƶ֡����1 2 3 4 �� 1000�� -n��������Ƶ֡����-1001)
    */
    int req_idx;
    /* �Ǳ���
    * ģ�����ƣ�ͨ��ģ�� "common"��
        Ӣ��ģ��"english"��
        Ĭ��ֵΪ��common��
    */
    std::string domain;
    /* �Ǳ���
    * true: �ӱ�㣬Ĭ��ֵ false������ӱ��
    */
    bool add_pct;
    asr_params()
    {
        domain = "common";
        add_pct = true;
    }
};

class asr_ws_example
{
public:
    static std::string get_token(const std::string& client_id, const std::string& client_secret);
    static std::string gen_json_request(const std::string& token, const std::string& version, const asr_params& params);
public:
    asr_ws_example(const std::string& filename, const std::string& access_token, const std::string& version, const asr_params& params);
    virtual ~asr_ws_example();
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
private:
    void work_thread();
#ifdef __ASR_REALTIME_ENABLE__
    void recv_asr_realtime_msg(const std::string& msg);
#else
    void recv_asr_msg(const std::string& msg);
#endif // __ASR_REALTIME_ENABLE__
private:
    client                              ws_client_;
    websocketpp::connection_hdl         hdl_;
    boost::mutex                        hdl_mutex_;
    boost::thread*                      work_thread_;
    std::string                         input_filename_;
    std::string                         access_token_;
    std::string                         version_;
    asr_params                          asr_params_;
};

#endif // __WSTTS_EXAMPLE_H__
