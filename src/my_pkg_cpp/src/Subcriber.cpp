#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

class SubscriberNode : public rclcpp::Node
{
    public: 
        SubscriberNode(): Node("sub_node")
        {
            sub_ = this->create_subscription<std_msgs::msg::String>("topic",1,
                std::bind(&SubscriberNode::topic_callback,this,std::placeholders::_1)) ;
            RCLCPP_INFO(this->get_logger(),"Subscriber Node has been started.") ;
        }
    private:
        void topic_callback(const std_msgs::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(),"I heard: '%s'", msg->data.c_str()) ;
        }

        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_ ;

} ;

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv) ; 
    auto node = std::make_shared<SubscriberNode>() ;
    rclcpp::spin(node) ;
    rclcpp::shutdown() ;
    return 0 ;
}