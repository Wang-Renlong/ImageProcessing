/* ֱ��ͼ��ͳ�����
*  Author: Wang RenLong
*  All rights reserved
*/
#pragma once

#ifndef STASTICS_HPP
#define STASTICS_HPP

#include "../stdafx.h"

#include "../base/pixel.h"


namespace stastics{
	/*ֱ��ͼ
     //��������Ҷ�ͼ��
     @src ����ͼ��
     @grap ���ͼ��, �������ֱ��ͼ
    */
	void countGray(Pixel* src, Pixel* grap);
	/*ֱ��ͼ-�����ֵ
     //��������Ҷ�ͼ��
    
     @src ����ͼ��
     @grap ���ͼ��, �������ֱ��ͼ
     @t1 ��һ��ֵ, ��ɫΪR^200, �粻��Ҫ����-1
     @t2 ��һ��ֵ, ��ɫΪG^200, �粻��Ҫ����-1
    */
	void countGrayWinthT(Pixel* src, Pixel* grap, short t1, short t2);
	/*�Ҷ�ֱ��ͳ��
     //��������Ҷ�ͼ��
    
     @src ����ͼ��
     @counts �����ͳ�ƽ������
     @counts_len counts���鳤��
    */
	void countGray(Pixel* src, unsigned int* counts, unsigned int counts_len);


} // namespace end

#endif //STASTICS_HPP

