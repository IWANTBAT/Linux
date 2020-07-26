#include<iostream>
#include<sstream>
#include<memory>
#include<string>
#include<json/json.h>

using  namespace std;

int main()
{
    std::string str =  "{\"Age\" : 26,\"Lang\" : \"c++\",\"Name\" : \"zhangsan\"}"; 

    std::cout<<str<<std::endl;

    JSONCPP_STRING errs; 
    Json::Value root; 
    Json::CharReaderBuilder rb; 
    std::unique_ptr<Json::CharReader> const jsonReader(rb.newCharReader());
    bool res = jsonReader->parse(str.data(), str.data()+str.size(), &root, &errs); 
    if(!res || !errs.empty()){
        std::cerr << "json parse error: " << errs << std::endl;
        return 1;
    }

    std::cout << "Name: " << root["Name"].asString() << std::endl;
    std::cout << "Age: " << root["Age"].asInt() << std::endl;
    std::cout << "Lang: " << root["Lang"].asString() << std::endl; 












   // Json::Value root;
   // Json::StreamWriterBuilder wb;
   // std::ostringstream os;

   // root["name"] = "张三";
   // root["age"] = 29;
   // root["lang"] = "c++";

   // std::unique_ptr<Json::StreamWriter> jw(wb.newStreamWriter()); 
   // jw->write(root,&os);
   // std::string result = os.str();

   // cout<<result<<endl;


    return 0;
}
