import subprocess
import time
import serial

# 본인의 아두이노 나노 포트 이름으로 수정
PORT = '/dev/cu.usbserial-3110'
BAUD = 9600

# 시리얼 통신 연결
try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)  # 아두이노 리셋 대기 시간
    print(f"아두이노 연결 성공: {PORT}")
except Exception as e:
    print(f"아두이노 연결 실패: {e}")
    exit()

def get_mac_battery():
    """맥북의 현재 배터리 잔량(%)을 정수로 반환하는 함수"""
    try:
        result = subprocess.run(['pmset', '-g', 'batt'], capture_output=True, text=True)
        output = result.stdout
        
        for line in output.split('\n'):
            if '%' in line:
                percent_str = line.split('%')[0].split()[-1]
                return int(percent_str)
    except Exception as e:
        print(f"배터리 정보 읽기 에러: {e}")
    return None

def send_mac_notification(title, message):
    """맥북 우측 상단에 네이티브 알림 팝업을 띄우는 함수"""
    script = f'display notification "{message}" with title "{title}"'
    subprocess.run(['osascript', '-e', script])

print("맥북 배터리 모니터링 시작 (종료하려면 Ctrl + C)")

# 알림이 너무 자주 울리는 것을 방지하기 위한 상태 변수
alert_sent = False

try:
    while True:
        battery = get_mac_battery()
        
        if battery is not None:
            print(f"현재 배터리 잔량: {battery}%")
            
            # 배터리 20% 이하일 때
            if battery <= 20:
                ser.write(b'1')  # 아두이노 LED 깜빡이기 신호 전송
                print("-> 배터리 부족! 경고등 켜기 신호 전송")
                
                # 아직 알림을 안 보낸 상태라면 맥북 팝업 알림 전송
                if not alert_sent:
                    send_mac_notification("배터리 부족 경고!", f"현재 배터리가 {battery}% 입니다. 충전기를 연결해주세요!")
                    alert_sent = True
            else:
                ser.write(b'0')  # 아두이노 LED 끄기 신호 전송
                print("-> 정상 상태 (LED 끄기)")
                alert_sent = False  # 배터리가 다시 충전되면 알림 상태 초기화
        
        # 60초마다 반복 체크
        time.sleep(60)

except KeyboardInterrupt:
    print("\n프로그램을 종료합니다.")
    ser.close()