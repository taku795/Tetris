#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <conio.h>


#define field_h 22
#define field_w 12

//�~�m�̌`���`
int mino[7][4][4][4]={
    //���
    {
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0}
        },
        {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
    },
    //2��
    {
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
    },
    //3��
    {
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },
    //4��
    {
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
    },
    //5��
    {
        {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
    },
    //6��
    {
        {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },
    //7��
    {
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },

};


int field[22][12];
int disbuf[22][12]={};
int mino_x,mino_y;
int shape,angle;

//338�s�܂�main���Ŏg���֐���`

//hit���Ă���1��Ԃ�
int hit () {
    int i,j;

    for (i=0;i<=3;i++) {
        for (j=0;j<=3;j++) {
            if ((field[mino_y+i][mino_x+j]==1) && (mino[shape][angle][i][j]==1)) {
            return 1;
            }
        }
    }
    return 0;
}

//�~�m���t�B�[���h�ɌŒ�
void mino_fix_on_field () {
    int i,j;

    for (i=0;i<=3;i++) {
        for (j=0;j<=3;j++) {
            field[mino_y+i][mino_x+j]+=mino[shape][angle][i][j];
        }
    }
}

//�~�m�̈ʒu�����������Č`�����߂�
void mino_decide (void) {
    srand((int)time(NULL));
    shape=(rand()%10000)%7;
    angle=rand()%4;
    mino_x=5;
    mino_y=1;
}

//�~�m��disbuf�ɃR�s�[
void mino_copy_disbuf (void) {
    int i,j;
    for (i=0;i<4;i++) {
        for (j=0;j<4;j++) {
            disbuf[mino_y+i][mino_x+j]+=mino[shape][angle][i][j];
        }
        
    }
}

//field��disbuf�ɃR�s�[
void field_copy_disbuf (void) {
    int i,j;
    for (i=0;i<field_h;i++) {
        for (j=0;j<field_w;j++) {
            disbuf[i][j]+=field[i][j];
        }
    }
}

//��]������
void rotate (void) {
    if (angle==3) {
        angle=0;
    } else {
        angle++;
    }
    if (hit()==1) {
        if (angle==0) {
            angle=3;
        } else {
            angle--;
        }
    }
}

//dis������
void initialize_disbuf (void) {
    int i,j;
    for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                disbuf[i][j]=0;
            }
        }
}

//disbuf�o��
void disbuf_out (void) {
    int i,j;

    system("cls");
        for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                if (disbuf[i][j]==1 || disbuf[i][j]==2) {
                    printf ("��");
                } else {
                    printf("��");
                }
            }
            printf ("\n");
        }
}

//�t�B�[���h���`�F�b�N���Ă�����񑵂��Ă��������
void field_cheack_and_delet_one_rine (void) {
    int i,j,k,count=0;

    for (i=field_h-2;i>=1;i--) {
        for (j=1;j<field_w-1;j++) {
        if (field[i][j]==1) {
            count++;
         } else {
            count=0;
        }

        }
        if (count>=10) {
            count=0;
            for (k=i;k>=2;k--) {
                for (j=1;j<field_w-1;j++) {
                    field[k][j]=field[k-1][j];
                    field[k-1][j]=0;
                }
            }
            i++;
        }
    }
}

int main (void)
{
    //i,j��for�Ŏg���p
    int i,j;
    time_t t;
    t=time(NULL);

    //�O�g��`//
    for (i=0;i<field_h;i++) {
        for (j=0;j<field_w;j++) {
            field[i][0]=1;
            field[i][field_w-1]=1;
            field[0][j]=1;
            field[field_h-1][j]=1;
        }
    }

    //�~�m�̈ʒu�����������Č`�����߂�
    mino_decide();

    while (1)
    {
        //dis������
        initialize_disbuf();

        //�~�m�����炷
        if (_kbhit())
        {
            switch (getch())
            {
                case 'a':
                    mino_x--;
                    if (hit()==1) {
                        mino_x++;
                    }
                break;
                case 's':
                    //�؂�Ń~�m�𓮂���
                    mino_y++;
                    if (hit()==1) {
                        //������������~�m��߂�
                        mino_y--;
                        //�~�m���t�B�[���h�ɌŒ�
                        mino_fix_on_field();
                        //�t�B�[���h���`�F�b�N���Ă�����s�����Ă������
                        field_cheack_and_delet_one_rine();
                        //�~�m�̈ʒu�����������Č`�����߂�
                        mino_decide();
                    }
                break;
                case 'd':
                    //�؂�Ń~�m�𓮂���
                    mino_x++;
                    if (hit()==1) {
                        //����������~�m��߂�
                        mino_x--;
                        }
                break;
                case 0x20:
                    //��]
                    rotate();
                break;               
                default:
                //�������Ȃ�
                break;
            }
            //�~�m�R�s�[
            mino_copy_disbuf();
            //field�R�s�[
            field_copy_disbuf();
            
            //dis�o��
            disbuf_out();

            //2�ȏオ�Ȃ������肷�邱�Ƃŏ�ɓ������Ă��Ȃ����m�F�A�������Ă�����I��
            for (i=0;i<field_h;i++) {
                for (j=0;j<field_w;j++) {
                    if (disbuf[i][j]>=2) {
                        return 0;
                    }
                }
            }
            
            //dis������
            initialize_disbuf();

        }//�{�^���������ꂽ��

        if (t!=time(NULL)) {
            t=time(NULL);
            //�~�m�~��
            mino_y++;

            if (hit()==1) {
                mino_y--;
                //�~�m���t�B�[���h�ɃR�s�[
                mino_fix_on_field();
                //�t�B�[���h���`�F�b�N���ď���
                field_cheack_and_delet_one_rine();
                //�~�m�̈ʒu�����������Č`�����߂�
                mino_decide();
                
            }//�~�m��������hit������
        }//���Ԃ��l�����ꂽ��

        //field�R�s�[
        field_copy_disbuf();
    
        //�~�m�R�s�[
        mino_copy_disbuf();

        //dis�o��
        disbuf_out();

        //2�ȏオ�Ȃ������肷�邱�Ƃŏ�ɓ������Ă��Ȃ����m�F�A�������Ă�����I��
        for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                if (disbuf[i][j]>=2) {
                    return 0;
                }
            }
        }
    }//���[�v�I��
    return 0;
}