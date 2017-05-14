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
	static const unsigned int FIFO_ERROR_ADMIN_NOT_LOGGED = -3;
	static const unsigned int FIFO_ERROR_EXISTENT_USER = -4;


	Management(T admin) {
		this->_manager_id = admin;
		_admin_logged = false;
	}

	int admin_login(T user){
		if(user == _manager_id){
			_admin_logged=true;
			return 0;
		}
		return -1;
	}
	int admin_logoff(){
		_admin_logged=false;
	}

	int add (T user){
		if(user==_manager_id)return FIFO_ERROR_ADMIN_NOT_LOGGED;

		if(_admin_logged){
			if(search(user)>=0)return FIFO_ERROR_EXISTENT_USER;

			if(_db_users.push(user) < 0) {
				return _db_users.FIFO_ERROR_FULL;
			}else{
				return 0;
			}

		}
	}
	int del(T user){
		if(user==_manager_id)return -1;


		if(_admin_logged){

			if(_db_users.size()  <=  0) {
				return _db_users.FIFO_ERROR_EMPTY;
			}else{
				if(user == 0) _db_users.clear();
				else{
					T popped;
					int i=0;

					while(_db_users.size()>i){
						if((popped = _db_users.pop()) == user){
							return i;
						}
						_db_users.push(popped);
						i++;
					}
				}
				return 0;
			}
		}
	}

	int get_size_db(){
		return _db_users.size();
	}

	int search(T user){
		T popped;
		int i=0;

		while(_db_users.size()>i){
			if((popped = _db_users.pop()) == user){
				_db_users.push(popped);
				return i;
			}
			_db_users.push(popped);
			i++;
		}

		return -1;
	}

private:
	T _manager_id;
	static const int _n=32;
	FIFO<T, _n> _db_users;
	bool _admin_logged;
};

#endif /* MANAGEMENT_H_ */
