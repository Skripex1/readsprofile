#include <iostream>
#include "Connection/TCP.h"
#include "DataBase/DB_Manager.h"
#include "utils/utils.h"
int main() {
    TCP TCP_CONNECTION;
    TCP_CONNECTION.establish_tcp_connection();
    TCP_CONNECTION.start_listening();
    return 0;
}
