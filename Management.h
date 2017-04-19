/*
 * Management.h
 *
 *  Created on: 19 de abr de 2017
 *      Author: gabriel
 */

#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#include "FIFO.h"

template<typename T>
class Management {
public:
	Management() {
		this->_manager_id = 1111;
	}

	int add (T user){
		if(_db_users.push(user) < 0) {
			return _db_users.FIFO_ERROR_FULL;
		}else{
			return 0;
		}
	}

	int del(T user){
		if(_db_users.pop()  < 0) {
			return _db_users.FIFO_ERROR_EMPTY;
		}else{
			return 0;
		}
	}

	int get_size_db(){
		return _db_users.size();
	}

	T search(T user){

	}
private:
	T _manager_id;
	int _n = 32;
	FIFO<T, _n> _db_users;
};

#endif /* MANAGEMENT_H_ */
