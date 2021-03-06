#include "GetSocketData.h"

bool GetSocketData::GetString(SOCKET& source, std::string & _string)
{
	int bufferlength; //Holds length of the message
	if (!GetInt(source, bufferlength)) //Get length of buffer and store it in variable: bufferlength
		return false; //If get int fails, return false
	char * buffer = new char[bufferlength + 1]; //Allocate buffer
	buffer[bufferlength] = '\0'; //Set last character of buffer to be a null terminator so we aren't printing memory that we shouldn't be looking at
	int RetnCheck = recv(source, buffer, bufferlength, NULL); //receive message and store the message in buffer array, set RetnCheck to be the value recv returns to see if there is an issue with the connection

	_string = buffer; //set string to received buffer message
	delete[] buffer; //Deallocate buffer memory (cleanup to prevent memory leak)
	if (RetnCheck == SOCKET_ERROR) //If connection is lost while getting message
		return false; //If there is an issue with connection, return false
	return true;//Return true if we were successful in retrieving the string
}

bool GetSocketData::GetPacketType(SOCKET* source, Packet & _packettype)
{
	int RetnCheck = recv(*source, (char*)&_packettype, sizeof(Packet), NULL); //receive packet type (same as integer)
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not properly get the packet type
	return true;//Return true if we were successful in retrieving the packet type
}

bool GetSocketData::GetInt(SOCKET& source, int & _int)
{
	int RetnCheck = recv(source, (char*)&_int, sizeof(int), NULL); //receive integer
	if (RetnCheck == SOCKET_ERROR) //If there is a connection issue
		return false; //return false since we did not get the integer
	return true;//Return true if we were successful in retrieving the int
}

GetSocketData::GetSocketData()
{
}


GetSocketData::~GetSocketData()
{
}
