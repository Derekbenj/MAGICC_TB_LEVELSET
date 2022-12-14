#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "curses.h"

int main(int argc, char** argv)
{

    // CURSES
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    WINDOW *win = newwin(LINES - 1, COLS - 1, 0, 0);
    nodelay(win, TRUE);
    scrollok(win, TRUE);
    wmove(win, 0, 0);

    // ros initialization code
    ros::init(argc, argv, "key_listener_sender");
    ros::NodeHandle n;

    // ros publisher
    ros::Publisher cmd_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
    ros::Rate loop_rate(100);

    // start loop for listening for keypresses!

    int new_key;
    int count = 0;

    while (ros::ok())
    {
        if ((new_key = getch()) == ERR)
        {
            //continue; we don't just want to continue... we want ros to take over and limit our message passing frequency... just have it skip the conditionals
            // by not doing anything.
        }
        else if (new_key == 'x')
        {
            ros::shutdown();
        }
        else
        {
            geometry_msgs::Twist msg;

            count++;
            switch (new_key)
            {
            case KEY_UP:
                wprintw(win, "%d: [up]\n", count);
                wrefresh(win);
                //ROS_INFO("Saw Keypress: [%d]\n", 1);
                msg.linear.x = 0.3;
                cmd_pub.publish(msg);
                break;
            case KEY_DOWN:
                wprintw(win, "%d: [down]\n", count);
                wrefresh(win);
                //ROS_INFO("Saw Keypress: [%d]\n", 2);
                msg.linear.x = -0.3;
                cmd_pub.publish(msg);
                break;
            case KEY_LEFT:
                wprintw(win, "%d: [left]\n", count);
                wrefresh(win);
                //ROS_INFO("Saw Keypress: [%d]\n", 3);
                msg.angular.z = 0.3;
                cmd_pub.publish(msg);
                break;
            case KEY_RIGHT:
                wprintw(win, "%d: [right]\n", count);
                wrefresh(win);
                //ROS_INFO("Saw Keypress: [%d]\n", 4);
                msg.angular.z = -0.3;
                cmd_pub.publish(msg);
                break;
            case KEY_RESIZE:
                wprintw(win, "%d: [RESIZE]\n", count);
                wresize(win, LINES - 1, COLS - 1);
                break;
            default:
                wprintw(win, "%d: ~~~\n", count);
                wrefresh(win);
                //ROS_INFO("Saw Keypress: [~~~]");
                //keys_pub.publish(new_key);
                break;
            }
        }
        ros::spinOnce();   // not necesary here: added to help remind that if we ever needed a subscription this calls the callback
        loop_rate.sleep(); // sleep the remaining time necesary until we meet the desired frequency
    }

    endwin();
}