1. ip확인   
   ping으로 확인함 

2. 리눅스 방화벽 비활성화 
   일부 포트만 열어주는것도 가능하나 여기서는 방화벽을 모두 내렸음. 
   sudo ufw disable     >> 비활성화
   sudo ufw enable     >>  활성화
   sudo ufw allow 22/tcp  >> 22포트 tcp만 허용

참고
https://webdir.tistory.com/206

3. 포트 
 포트 설정 및 저장은  하이퍼레저SDK.xlsx 의 WAS 설정을 참고

 - 포트 확인 
   sudo iptables -L -v  

4. 간이 TCP 서버 테스트
서버
#nc -l -p 1234

클라이언트  //localhost에 ip 입력 가능함.
#telnet localhost 1234     

//간단하게 nc로 tcp 서버와 클라이언트 테스트 
https://devanix.tistory.com/307

//서버 소스
https://nroses-taek.tistory.com/87

5. TCP 서버 동작 방법
소스위치 :  ~/work/dab/server_taskone.c
gcc server_taskone.c -o server

port 1234  로 설정함. 
클라이언트에서 입력되는 사이즈는 1024byte

"0"를 입력하면 마이크 실행됨
"2"를 입력하면  audio2_enc.sh 실행됨
"3"를 입력하면  audio3_enc.sh 실행됨
..."7" 까지 입력하면 실행되게 함.
"q"를 입력하면 접속이 종료됨

server 종료 ctrl + c   

6. 예외상황
server를 내리고 동작 시킬때 동작이 안되고
bind : address already in use....     나올땐
netstat -lntp     
입력 후 해당 포트가 사용되는것을 찾아서 kill 해준다.
sudo kill -9 pid번호

만약 netstat -lntp 해도 나타나지 않으면 timewate에 걸린것이므로 time 셋팅된 
시간이후에 다시 실행하면 동작한다. 그래도 안되면 재부팅을 권함.



