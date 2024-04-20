#include "Texture.h"

void Texture::load(std::string filename)
{
	// ������� ����� "�����������"
	ILuint imageId = ilGenImage();
	// ������ ������� "�����������"
	ilBindImage(imageId);

	// ��������� �����������
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool result = ilLoadImage(unicodeString);

	if (result) {
		// ��������� ���������� ����������� ��������
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		//��� ������������� ������� RGBA � ���� ������ IL_UNSIGNED_BYTE,
		//����� �������� ������ ��� ������� ��������
		//width * height * depth * 4 ����.
		int dataSize = width * height * 1 * 4;
		void* data = new unsigned char[dataSize];

		//������� ilCopyPixels ��������� �����������
		//������ �������� �� ���������� ������ ���������� DevIL � ��������� ������,
		//������������� � ����������� ������.
		ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);

		// ������� �����������
		ilDeleteImage(imageId);

		// ���������� ������ ������ (��������� ����������)
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//������ 0 ��������� ���� ��������
		glActiveTexture(GL_TEXTURE0);
		//�������� ����������� �������
		glGenTextures(1, &texIndex);
		//�������� ����������� ������� � ����������� �����
		glBindTexture(GL_TEXTURE_2D, texIndex);
		//�������� ����������� �� ����������� ������ � ���������� ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete[] reinterpret_cast<unsigned char*>(data);
		//��������� mipmap���
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::apply(TextureFilter texFilter)
{
	// ��������� ���������� ��������
	switch (texFilter) {
		case TextureFilter::POINT:
			// ��������� ���������� �������� � �������� �����
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;

		case TextureFilter::BILINEAR:
			// ��������� ���������� �������� � ���������� �����
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case TextureFilter::TRILINEAR:
			// ��������� ���������� �������� � ����������� �����
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case TextureFilter::ANISOTROPIC:
			// ��������� ���������� �������� � ������������ �����
			GLfloat maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
			break;
	}
	// ����������� ���������� ������ � ����������� �����
	glBindTexture(GL_TEXTURE_2D, texIndex);
}

void Texture::disableAll()
{
	glDisable(GL_TEXTURE_2D);
}
