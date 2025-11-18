#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>

class PublisherNode : public rclcpp::Node 
{
    public:
        PublisherNode(): Node("publisher_node"), count_(0)
        {
            publisher_= this->create_publisher<std_msgs::msg::String>("topic", 10);
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                            std::bind(&PublisherNode::publish_message, this));
            RCLCPP_INFO(this->get_logger(), "Publisher Node has been started.");
        }
    private:
        void publish_message()
        {
            auto message = std_msgs::msg::String();
            message.data = "Hello, ROS2! Count: " + std::to_string(count_++);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
            publisher_->publish(message);
        }
        size_t count_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}