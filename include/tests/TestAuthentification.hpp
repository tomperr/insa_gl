#ifndef TEST_AUTHENTIFICATION_HPP
#define TEST_AUTHENTIFICATION_HPP

#include <iostream>
#include <assert.h>
#include "Authentification.hpp"
#include "User.hpp"
#include "User_profile.hpp"

void ResetAuthentification();

void test_is_auth_ok1();
void test_is_auth_ok2();
void test_auth_ok1();
void test_auth_ok2();
void test_auth_ko();
void test_deauth_ok();
void test_deauth_ko1();
void test_deauth_ko2();
void test_getuser_ok1();
void test_getuser_ok2();
void test_getuser_limit();
void test_integration_ok();

#endif