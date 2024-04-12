#ifndef __AUTH_HEADER__
#define __AUTH_HEADER__

/**
 * Tokens have three parts: operate, user, and the authority range.
 * operate include create, delete, select, update.
 * users include admin, worker, resident, self.
 * the range has the above 
 * - secure: password and username
 * - zone: the living or serving house
 * - fee: the fee which the resident should pay
 * - info: other infomations
 * - log: the paid log 
 */

#define _generator_finally(operate, user, auth) \
    operate##_##user##_##auth

#define _generator_auth(operate, user) \
    _generator_finally(operate, user, SECURE), \
    _generator_finally(operate, user, ZONE),   \
    _generator_finally(operate, user, FEE),    \
    _generator_finally(operate, user, INFO),   \
    _generator_finally(operate, user, LOG)

#define _generator_operator(operate) \
    _generator_auth(operate, ADMIN),    \
    _generator_auth(operate, WORKER),   \
    _generator_auth(operate, RESIDENT), \
    _generator_auth(operate, SELF)

#define _generator_tokens \
    _generator_operator(CREATE), \
    _generator_operator(DELETE), \
    _generator_operator(SELECT), \
    _generator_operator(UPDATE), \

enum token{
    _generator_tokens
};

#endif
