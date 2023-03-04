#pragma once

class IResponse {
public:
	virtual void BuildHeader() = 0;
	virtual void BuildBody() = 0;
	virtual int getBodyLength() = 0;
};