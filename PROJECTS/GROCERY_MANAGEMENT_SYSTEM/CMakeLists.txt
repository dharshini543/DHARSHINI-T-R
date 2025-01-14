cmake_minimum_required(VERSION 3.16)

project(GROCERY_MANAGEMENT_SYSTEM LANGUAGES C)

add_executable(GROCERY_MANAGEMENT_SYSTEM main.c
    billing.h
    billing.c
    cart.h
    cart.c
    enum.h
    inventory.h
    inventory.c
    inventory_FO.h
    inventory_FO.c
    report.h
    report.c
    sales_report_FO.h
    sales_report_FO.c
    sorting.h
    sorting.c
    start.h
    start.c
    user.h
    user.c)

include(GNUInstallDirs)
install(TARGETS GROCERY_MANAGEMENT_SYSTEM
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
