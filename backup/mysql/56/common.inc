#!/bin/bash

# --���ʊ֐���`--

#----------------
# ���O�o�͊֐�
#----------------

# ���O�w�b�_��������
# MSG�F�G���[���b�Z�[�W
# LOG_PATH�F���O�p�X
SetLOG_HEADER()
{
  # �����W�J
  FILENM=`basename $0`
  MSG=$1
  LOG_PATH=$2

  # �ϐ���`
  LOG_DATE=`GetYMD2`  # �N�����擾
  LOG_TIME=`GetTIME1` # �����擾

  # ���O�o�͎��s
  printf "%-10s %-8s %-14s %-50s\n" \
   "${LOG_DATE}" "${LOG_TIME}" "${FILENM}" "${MSG}" >>${LOG_PATH}
}

# ���O�ڍ׏�������
# MSG�F�G���[���b�Z�[�W
# LOG_PATH�F���O�p�X
SetLOG_DETAILS()
{
  # �����W�J
  FILENM=`basename $0`
  MSG=$1
  LOG_PATH=$2

  # �ϐ���`
  LOG_DATE=`GetYMD2`  # �N�����擾
  LOG_TIME=`GetTIME1` # �����擾

  # ���O�o�͎��s
  printf "%-10s %-8s %-14s %-50s\n" \
   "${LOG_DATE}" "${LOG_TIME}" "${FILENM}" "${MSG}" >>${LOG_PATH}
}

# ���O�t�b�^�[��������
# MSG�F�G���[���b�Z�[�W
# LOG_PATH�F���O�p�X
SetLOG_FOOTER()
{
  # �����W�J
  FILENM=`basename $0`
  MSG=$1
  LOG_PATH=$2

  # �ϐ���`
  LOG_DATE=`GetYMD2`  # �N�����擾
  LOG_TIME=`GetTIME1` # �����擾

  # ���O�o�͎��s
  printf "%-10s %-8s %-14s %-50s\n" \
   "${LOG_DATE}" "${LOG_TIME}" "${FILENM}" "${MSG}" >>${LOG_PATH}
}

#----------------
# �V�X�e���֐�
#----------------

# �N�����擾�֐��@
GetYMD1()
{
  SYSTEM_DATE=`date '+%Y%m%d'`
  echo ${SYSTEM_DATE}
}

# �N�����擾�֐��A
GetYMD2()
{
  SYSTEM_DATE=`date '+%Y-%m-%d'`
  echo ${SYSTEM_DATE}
}

# �N�����擾�֐��B
GetYMD3()
{
  SYSTEM_DATE=`date '+%Y/%m/%d'`
  echo ${SYSTEM_DATE}
}

# �N���擾�֐��@
GetYM1()
{
  SYSTEM_MONTH=`date '+%Y%m'`
  echo ${SYSTEM_MONTH}
}

# �����擾�֐��@
GetTIME1()
{
  SYSTEM_TIME=`date '+%H:%M:%S'`
  echo ${SYSTEM_TIME}
}

# �j���擾�֐�
GetWEEK()
{
  SYSTEM_WEEK=`date +%a`
  echo ${SYSTEM_WEEK}
}

# �j���擾�֐�
GetWEEK()
{
  SYSTEM_WEEK=`date +%a`
  echo ${SYSTEM_WEEK}
}

# ��΃p�X����t�@�C�������������o��
# $1�F��΃p�X
# $2�F�g���q
GetFILENAME_BY_PATH()
{
  echo `basename $1 $2`
}

# �v���Z�X�Ď�&�N��
# $1�F�N���m�F�v���Z�X
ChkPROC_SHELL()
{
  PROC_NAME=$1
  isAlive=`ps -ef | grep "${PROC_NAME}" | \
    grep -v grep | wc -l`
  if [ $isAlive = 1 ]; then
     isAlive=1
  else
    isAlive=0
  fi
  echo $isAlive
}


#----------------
# �f�B���N�g���֐�
#----------------


# �f�B���N�g���쐬
# DIR_PATH�F�쐬�p�X
Create_DIR()
{
  DIR_PATH=$1
  mkdir -p ${DIR_PATH}
}

# �f�B���N�g���ړ�
# CD_PATH�F�ړ��p�X
# MSG�F�G���[���b�Z�[�W
Dir_CD()
{
  CD_PATH=$1
  MSG=$2

  cd ${CD_PATH}
  if [ $? != 0 ]; then
   echo "${MSG} directory does not exist."
   exit 1
  fi
}

# �t�H���_���k
# BK_PATH�F���k��p�X
# FILENAME�F�o�b�N�A�b�v�t�@�C����
# ORG_PATH�F���k���p�X
Dir_TAR()
{
  BK_PATH=$1
  FILENAME=$2
  ORG_PATH=$3
  # "tar:Removing leading '/' from member names"
  cd ${ORG_PATH}
  tar cvzf ${BK_PATH}${FILENAME} ./
}

# �t�H���_�폜
# DIR_PATH�F�t�@�C���p�X
Dir_RM()
{
  DIR_PATH=$1
  rm -rf ${DIR_PATH}
}


#----------------
# �t�@�C���֐�
#----------------


# �t�@�C���R�s�[
# ORG_DIR_PATH�F�R�s�[���t�@�C���p�X
# ORG_FILENAME�F�t�@�C����
# SAKI_DIR_PATH�F�R�s�[��p�X
# SAKI_FILENAME�F�R�s�[�t�@�C��
File_CP()
{
  ORG_DIR_PATH=$1
  ORG_FILENAME=$2
  SAKI_DIR_PATH=$3
  SAKI_FILENAME=$4

  cp ${ORG_DIR_PATH}${ORG_FILENAME} ${SAKI_DIR_PATH}${SAKI_FILENAME}
}

# �t�@�C���폜
# DIR_PATH�F�t�@�C���p�X
# FILENAME�F�t�@�C����
File_RM()
{
  DIR_PATH=$1
  FILENAME=$2

  rm -f ${DIR_PATH}${FILENAME}
}

# �t�@�C���폜�����֐� (����)
# �X�V��������n���o�߂����w��t�@�C���`���̃t�@�C�����폜
# FILE_FORMAT�F�t�@�C���t�H�[�}�b�g
# BK_DIR�F�o�b�N�A�b�v�p�X
# BK_DAYS�F�ێ����镪��
DelFILE_BY_MIN_ONUPTIME()
{
  FILE_FORMAT=$1
  BK_DIR=$2
  BK_DAYS=$3
  find ${BK_DIR} -name "${FILE_FORMAT}" -type f -mmin +${BK_DAYS} -exec rm {} \;
}

# �t�@�C���폜�����֐� (����)
# �X�V��������n���o�߂����w��t�@�C���`���̃t�@�C�����폜
# FILE_FORMAT�F�t�@�C���t�H�[�}�b�g
# BK_DIR�F�o�b�N�A�b�v�p�X
# BK_DAYS�F�ێ��������
DelFILE_BY_DAY_ONUPTIME()
{
  FILE_FORMAT=$1
  BK_DIR=$2
  BK_DAYS=$3
  find ${BK_DIR} -name "${FILE_FORMAT}" -type f -mtime +${BK_DAYS} -exec rm {} \;
}

# �O���t�@�C���ǂݍ���
# FILE_PATH:�O���t�@�C���p�X
# �߂�l�F�z��
Read_OUTSIDE_FILE()
{
  FILE_PATH=$1
  # read �R�}���h�œǂݎ��Ȃ��Ȃ�܂Ń��[�v
  count=0

  while read LINE
  do
    #echo "$LINE"
    # �z��쐬
    ARRAY[$count]=$LINE
    # �J�E���g���Z
    count=`expr $count+1`
  done < ${FILE_PATH}

  echo ${ARRAY[@]}
}



#----------------
# ������֐�
#----------------


# ������u��
# TARGET�F�Ώە�����
# SEARCH_STR�F����������
# REPLACE_STR�F�u��������
Do_REPLACE_STR()
{
  TARGET=$1
  SEARCH_STR=$2
  REPLACE_STR=$3

  TARGET_FILE=`echo ${TARGET} | sed -e "s/${SEARCH_STR}/${REPLACE_STR}/"`

  echo ${TARGET_FILE}
}

# �ϐ����݃`�F�b�N�֐�
# �ϐ������ݒ�̏ꍇ�A��֕ϐ��ɒu��������
# TARGET�F�Ώە�����
# REPLACE_STR�F�u��������
Do_REPLACE_EMPTY()
{
  TARGET=$1
  REPLACE_STR=$2
  echo ${TARGET:-${REPLACE_STR}}
}

# �C�ӕ����񑶍݃`�F�b�N�֐�
# TARGET�F�Ώە�����
# SEARCH_STR�F����������
Do_GREP_STR()
{
  TARGET=$1
  SEARCH_STR=$2
  echo `grep "${SEARCH_STR}" ${TARGET}`
}


#----------------
# ���[���֐�
#----------------

# ���[�����M�֐�
# TOADDRESS�F���M�A�h���X
# SUBJECT�F����
# MSG�F���e
Do_SENDMAIL(){
  TOADDRESS=$1
  SUBJECT=$2
  MSG=$3

  echo -e "${MSG}" | mail -s "${SUBJECT}" "${TOADDRESS}"
}