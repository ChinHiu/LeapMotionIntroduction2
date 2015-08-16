#include <iostream>
#include <Leap.h>

class SampleListener : public Leap::Listener
{
    int handId;

public:

    SampleListener()
    {
        handId = -1;
    }

    void onFrame(const Leap::Controller& leap)
    {
        auto frame = leap.frame();

#if 0
    // ����̃t���[���Ō��o�������ׂĂ̎�A�w�A�c�[��
    Leap::HandList hands = frame.hands();
    Leap::FingerList fingers = frame.fingers();
    Leap::ToolList tools = frame.tools();
    Leap::PointableList pointables = frame.pointables();

    std::cout << "Frame Data : "
        << " Hands : " << hands.count()
        << " Fingers : " << fingers.count()
        << " Extended Fingers : " << fingers.extended().count()
        << " Tools : " << tools.count()
        << " Pointers : " << pointables.count()
        << std::endl;
#endif

#if 0
        // ���ID����A�������ǐՂ�������
        if ( handId == -1 ) {
            handId = frame.hands()[0].id();
        }
        else {
            Leap::Hand hand = frame.hand(handId);
            handId = hand.id();

            // ��̏���\������
            std::cout << "ID : " << hand.id()
                << " �ʒu : " << hand.palmPosition()
                << " ���x : " << hand.palmVelocity()
                << " �@�� : " << hand.palmNormal()
                << " ���� : " << hand.direction()
                << std::endl;
        }
#endif

#if 0
        // ��ԍ��A�E�A��O�̎���擾����
        Leap::HandList hands = frame.hands();
        Leap::Hand leftMost = hands.leftmost();
        Leap::Hand rightMost = hands.leftmost();
        Leap::Hand frontMost = hands.frontmost();

        std::cout << " �� : " << leftMost.palmPosition()
            << " �E : " << rightMost.palmPosition()
            << " ��O : " << frontMost.palmPosition()
            << std::endl;
#endif

#if 0
        // ��̏��擾����
        Leap::Hand hand = frame.hands()[0];

        std::cout << " �E�� : " << hand.isRight()
                  << " �s���` : " << hand.pinchStrength()
                  << " �O���u : " << hand.grabStrength()
                  << " �M���� : " << hand.confidence()
                  << std::endl;
#endif

#if 0
        // ��ɑ����Ă���w�ƃc�[�����擾����
        for ( auto hand : frame.hands() ) {
            std::cout << "ID : " << hand.id()
                      << " Fingers : " << hand.fingers().count()
                      << " Extended Fingers : " << hand.fingers().extended().count()
                      << " Tools : " << hand.tools().count()
                      << " Pointers : " << hand.pointables().count()
                      << std::endl;
        }
#endif

#if 0
        // �w�̏����擾����
        for ( auto finger : frame.fingers().extended() ) {
            std::cout << "ID : " << finger.id()
                      << " ��� : " << finger.type()
                      << " �ʒu : " << finger.tipPosition()
                      << " ���x : " << finger.tipVelocity()
                      << " ���� : " << finger.direction()
                      << std::endl;
        }
#endif

#if 1
        // �w�̊֐ߏ����擾����
        for ( auto finger : frame.fingers() ) {
            // ���ߍ�(�w��̍�)
            auto bone = finger.bone(Leap::Bone::TYPE_DISTAL);
            std::cout << "��� : " << bone.type()
                      << " ���S : " << bone.center()
                      << " ��[ : " << bone.prevJoint()
                      << " ���[ : " << bone.nextJoint()
                      << std::endl;
        }
#endif

#if 1
        // �e�w�̒�`���m�F����
        for ( auto finger : frame.fingers() ) {
            if ( finger.type() == Leap::Finger::Type::TYPE_THUMB ){
                for ( int t = Leap::Bone::TYPE_METACARPAL;  t <= (int)Leap::Bone::TYPE_DISTAL; ++t ){
                    auto bone = finger.bone( (Leap::Bone::Type)t );
                    std::cout << "��� : " << bone.type()
                              << " ���� : " << bone.length() << std::endl;
                }
            }
        }
#endif
    }
};

int main(int argc, const char * argv[])
{
    SampleListener listener;
    Leap::Controller leap(listener);

    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    return 0;
}
