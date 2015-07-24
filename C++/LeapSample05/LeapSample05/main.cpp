#include <iostream>
#include <Leap.h>

#define SAMPLE_NO 1

// �|�[�����O�����̗�
#if SAMPLE_NO == 1
void main()
{
    Leap::Controller leap;
    int64_t previousFrameId = -1;

    // �����������ioninit()�����j�������ɏ���

    // �������[�v���ŁA�O��̃t���[����ID�Ɣ�r���ĐV�����t���[�����擾����
    while ( 1 ) {
        auto frame = leap.frame();
        if ( previousFrameId == frame.id() ) {
            continue;
        }

        previousFrameId = frame.id();

        // �t���[���X�V�����ionFrame()�����j�������ɏ���
    }

    // �I�������ionExit()�����j�������ɏ���
}
#endif


// �|�[�����O���̐ڑ���Ԃ���уt�H�[�J�X��Ԃ��擾����
#if SAMPLE_NO == 2
void main()
{
    bool isPrevConnected = false;
    bool isPrevServiceConnected = false;
    bool hadPrevFocus = false;
    int64_t previousFrameId = -1;

    Leap::Controller leap;

    // ����������(oninit()����)

    while ( 1 ) {
        auto frame = leap.frame();

        // Leap Motion�R���g���[���[�Ƃ̐ڑ���Ԃ��m�F����
        {
            bool isCurrentConnected = leap.isConnected();
            if ( isPrevConnected != isCurrentConnected ) {
                if ( isCurrentConnected ) {
                    // Leap Motion �R���g���[���[���ڑ����ꂽ(onConnected()����)
                    std::cout << "Leap Motion Controller connected." << std::endl;
                }
                else {
                    // Leap Motion �R���g���[���[�������ꂽ(onDisconnected()����)
                    std::cout << "Leap Motion Controller disconnected." << std::endl;
                }
            }

            isPrevConnected = isCurrentConnected;
        }

        // Leap Motion�T�[�r�X�Ƃ̐ڑ���Ԃ��m�F����
        {
            bool isCurrentServiceConnected = leap.isServiceConnected();
            if ( isPrevServiceConnected != isCurrentServiceConnected ) {
                if ( isCurrentServiceConnected ) {
                    // Leap Motion�T�[�r�X���ڑ����ꂽ(onServiceConnect()����)
                    std::cout << "Leap Motion Service connected." << std::endl;
                }
                else {
                    // Leap Motion�T�[�r�X���ؒf���ꂽ(onServiceDisconnect()����)
                    std::cout << "Leap Motion Service disconnected." << std::endl;
                }
            }

            isPrevServiceConnected = isCurrentServiceConnected;
        }

        // �t�H�[�J�X��Ԃ��m�F����
        {
            bool hadCurrentFocus = leap.hasFocus();
            if ( hadPrevFocus != hadCurrentFocus ) {
                if ( hadCurrentFocus ) {
                    // �A�v���P�[�V�����̃t�H�[�J�X���L���ɂȂ���(onFocusGained()����)
                    std::cout << "Focus gained." << std::endl;
                }
                else {
                    // �A�v���P�[�V�����̃t�H�[�J�X�������ɂȂ���(onFocusLost()����)
                    std::cout << "Focus lost." << std::endl;
                }
            }

            hadPrevFocus = hadCurrentFocus;
        }

        // �t���[�����X�V����Ă��Ȃ���Ή������Ȃ�
        {
            if ( previousFrameId == frame.id() ) {
                continue;
            }

            previousFrameId = frame.id();
        }

        // �t���[���X�V����(onFrame()����)
    }

    // �I������(onExit()����)
}
#endif

// ���O�̃t���[�����擾����
#if SAMPLE_NO == 3
void main()
{
    Leap::Controller leap;
    int64_t previousFrameId = -1;

    while ( 1 ) {
        // �ŐV�̃t���[�����擾���� (leap.frame( 0 ) �Ɠ���)
        auto currentFrame = leap.frame();
        if ( previousFrameId == currentFrame.id() ) {
            continue;
        }

        previousFrameId = currentFrame.id();

        // ���O��5�t���[�����擾����
        std::cout << currentFrame.id() << ", ";
        for ( int i = 1; i <= 5; ++i ) {
            auto previousFrame = leap.frame(i);
            std::cout << previousFrame.id() << ", ";
        }
        std::cout << std::endl;
    }

    // �I������(onExit()����)
}
#endif


#if SAMPLE_NO == 4
void main()
{
    Leap::Controller leap;

    int64_t lastFrame = 0;

    // ����������(oninit()����)

    while ( 1 ) {
        auto frame = leap.frame();
        if ( !leap.isConnected() ) {
            std::cout << "leap is not connected." << std::endl;
            continue;
        }

        bool focus = leap.hasFocus();
        if ( !focus ) {
            std::cout << "application is not focus." << std::endl;
            continue;
        }

        auto currentFrameid = frame.id();
        if ( currentFrameid == lastFrame ) {
            //std::cout << "processed frame id." << std::endl;
            continue;
        }

        // �O��ƍ���̃t���[������
        //std::cout << "frame count : " << (currentFrameid - lastFrame) << std::endl;

        lastFrame = currentFrameid;

        // �w�̈ʒu�̕��ϒl���v�Z����
        int count = 0;
        Leap::Vector average = Leap::Vector();
        Leap::Finger fingerToAverage = frame.fingers()[0];
        for ( int i = 0; i < 10; i++ ) {
            // �t���[�������Ǝw��ID�ŁA�ߋ��̎w�̈ʒu���擾����
            Leap::Finger fingerFromFrame = leap.frame(i).finger(fingerToAverage.id());
            if ( fingerFromFrame.isValid() ) {
                average += fingerFromFrame.tipPosition();
                count++;
            }
        }

        if ( count > 0 ) {
            average /= count;
            std::cout << "finger point : " << average << std::endl;
        }
    }

    // �I������(onExit()����)
}
#endif

#if SAMPLE_NO == 5
// �|�[�����O�Ńt���[�����擾����
void GettingFramesByPolling()
{
    Leap::Controller leap;

    int64_t lastFrame = 0;
    while ( 1 ) {
        auto frame = leap.frame();
        if ( !leap.isConnected() ) {
            std::cout << "leap is not connected." << std::endl;
            continue;
        }

        bool focus = leap.hasFocus();
        if ( !focus ) {
            std::cout << "application is not focus." << std::endl;
            continue;
        }

        auto currentFrameid = frame.id();
        if ( currentFrameid == lastFrame ) {
            //std::cout << "processed frame id." << std::endl;
            continue;
        }

        //std::cout << "frame count : " << (currentFrameid - lastFrame) << std::endl;

        lastFrame = currentFrameid;

        // �w�̈ʒu�̕��ϒl���v�Z����
        int count = 0;
        Leap::Vector average = Leap::Vector();
        Leap::Finger fingerToAverage = frame.fingers()[0];
        for ( int i = 0; i < 10; i++ ) {
            // �t���[�������Ǝw��ID�ŁA�ߋ��̎w�̈ʒu���擾����
            Leap::Finger fingerFromFrame = leap.frame(i).finger(fingerToAverage.id());
            if ( fingerFromFrame.isValid() ) {
                average += fingerFromFrame.tipPosition();
                count++;
            }
        }
        average /= count;
        std::cout << "finger point : " << average << std::endl;
    }
}

// �R�[���o�b�N(�C�x���g�쓮)�ŃC�x���g���擾����
class SampleListrener : public Leap::Listener
{
public:

    virtual void onFocusGained(const Leap::Controller&) {
        std::cout << __FUNCTION__ << std::endl;
    }

    virtual void onFocusLost(const Leap::Controller&) {
        std::cout << __FUNCTION__ << std::endl;
    }

};

void GettingFramesWithCallbacks()
{
    SampleListrener listner;
    Leap::Controller leap;
    leap.addListener(listner);

    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    leap.removeListener(listner);
}

// �t���[���̎����̃T���v��
int main()
{
#if 0
    // �|�[�����O
    GettingFramesByPolling();
#else
    // �R�[���o�b�N
    GettingFramesWithCallbacks();
#endif

    return 0;
}
#endif

