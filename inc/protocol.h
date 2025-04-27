#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <string>
#include <vector>



//From master
namespace MasterToSlave {
	enum class MessageType {
		MANAGEMENT,	//TODO
		MAINTENANCE,	//TODO
		JOIN_ACK,	//Successfull join of slave
		LEAVE_ACK	//Successfull leave of slave
	};
}

namespace MasterToClient {
	enum class MessageType {
		OPEN_META,	//Report to client where to read
		WRITE_META,	//Report to client where to write
		OPEN_ERROR,	//TODO: error codes
		WRITE_ERROR,	//TODO: error codes
		RESPONSE_ERROR, //TODO: error codes
		RESPONSE_SUCCESS
	};
}

//From slave
namespace SlaveToMaster {
	enum class MessageType {
		HEARTHBEAT,
		BLOCK_REPORT,
		BLOCK_REC_ACK,
		ERROR, //TODO: error codes
		JOIN_REQ,
		LEAVE_REQ
	};
}

namespace SlaveToClient {
	enum class MessageType {
		BLOCK_READ,
		BLOCK_ERROR,
		BLOCK_NOT_FOUND
	};
}

//From client
namespace ClientToMaster {
	enum class MessageType {
		REQUEST_OPEN,
		REQUEST_WRITE,
		REQUEST_DELETE,
		REQUEST_READ,
		ERROR,
		REQUEST_EXISTENCE
	};
}

namespace ClientToSlave {
	enum class MessageType {
		WRITE_BLOCK,
		READ_BLOCK
	};
}
//----------------------
enum class MessageType {
    CLIENT_REQUEST_OPEN, #Client->Master
    CLIENT_REQUEST_WRITE,
    CLIENT_REQUEST_READ,
    MASTER_RESPONSE_METADATA,
    SLAVE_STORE_BLOCK,
    SLAVE_HEARTBEAT,
    ERROR_RESPONSE
    // Add more as needed
};

struct MessageHeader {
    MessageType type;
    uint32_t payloadSize; // size of the payload following the header
};

struct ClientRequestOpen {
    std::string filename;
};

struct ClientRequestWrite {
    std::string filename;
    std::vector<char> data;
};

struct MasterResponseMetadata {
    std::vector<std::string> slaveAddresses; // IPs or IDs where file blocks are located
};

struct SlaveHeartbeat {
    std::string slaveId;
    uint64_t timestamp;
};

// etc...
#endif
