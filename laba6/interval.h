#include <cmath>

#define TYPE double

struct interval 
{
	TYPE left;
	TYPE right;
};

interval fold(interval A,interval B)
{
	interval C;
	C.left=A.left+B.left;
	C.right=A.right+B.right;
	return C;
}

interval fold(interval A,TYPE B)
{
	interval C;
	C.left=A.left+B;
	C.right=A.right+B;
	return C;
}

interval fold(TYPE A,interval B)
{
	interval C;
	C.left=A+B.left;
	C.right=A+B.right;
	return C;
}

interval subtraction(interval A,interval B)
{
	interval C;
	C.left=A.left-B.right;
	C.right=A.right-B.left;
	return C;
}

interval subtraction(interval A,TYPE B)
{
	interval C;
	C.left=A.left-B;
	C.right=A.right-B;
	return C;
}

interval subtraction(TYPE A,interval B)
{
	interval C;
	C.left=A-B.right;
	C.right=A-B.left;
	return C;
}

interval multiply(interval A,interval B)
{
	interval C;
	TYPE buf;
	C.left=(double)A.left*B.left;
	C.right=(double)A.left*B.right;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}
	buf=(double)A.right*B.left;
	if (C.left>buf)
	{
		C.left=buf;
	}
	if (C.right<buf)
	{
		C.right=buf;
	}
	buf=(double)A.right*B.right;
	if (C.left>buf)
	{
		C.left=buf;
	}
	if (C.right<buf)
	{
		C.right=buf;
	}	
	return C;
}

interval multiply(TYPE A,interval B)
{
	interval C;
	TYPE buf;
	C.left=(double)A*B.left;
	C.right=(double)A*B.right;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}	
	return C;
}

interval multiply(interval A,TYPE B)
{
	interval C;
	TYPE buf;
	C.left=(double)A.left*B;
	C.right=(double)A.right*B;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}	
	return C;
}

interval divide(interval A,interval B)
{
	interval C;
	TYPE buf;
	C.left=(double)A.left/(double)B.left;
	C.right=(double)A.left/(double)B.right;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}
	buf=(double)A.right/(double)B.left;
	if (C.left>buf)
	{
		C.left=buf;
	}
	if (C.right<buf)
	{
		C.right=buf;
	}
	buf=(double)A.right/(double)B.right;
	if (C.left>buf)
	{
		C.left=buf;
	}
	if (C.right<buf)
	{
		C.right=buf;
	}	
	return C;
}

interval divide(interval A,TYPE B)
{
	interval C;
	TYPE buf;
	C.left=(double)A.left/(double)B;
	C.right=(double)A.left/(double)B;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}	
	return C;
}

interval divide(TYPE A,interval B)
{
	interval C;
	TYPE buf;
	C.left=(double)A/(double)B.left;
	C.right=(double)A/(double)B.right;
	if (C.left>C.right)
	{
		buf=C.left;
		C.left=C.right;
		C.right=buf;
	}
	return C;
}
interval sqrtinter(interval A)
{
	interval C;
	C.left=sqrt(A.left);
	C.right=sqrt(A.right);
	return C;
}
