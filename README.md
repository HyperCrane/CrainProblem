# CrainProblem
소프트웨어 설계 크레인 운영 시스템 팀 프로젝트 연습문제입니다

----
#Crane System
x,y 좌표에 있는 물건을 x2,y2 좌표로 
Motor 1: x 축 움직임을 제어한다. 
Motor 2: y 축 움직임을 제어한다. 
Motor 3: 집게(손)를 up, down한다. (1:up, 0:down)
집게는 5개의 손가락으로 구성되어 있고 각각의 손가락은 motor 4,5,6,7,8이 제어한다. 0:펴기, 1: 굽히기
제한조건 모든 모터는 현재의 상태를 정확하게 파악하고 있다가 제어 명령이 들어오면 현상태와 비교하여 움직임을 결정한다.
제한조건 : 현재 손가락이 편 상태인데 펴라는 명령이 들어오면 제어를 하지 않아야 한다. 

#기능 
Down, Grab, Up, Right, Down, Let go, Up, Right, Down, Grab, Up, Left, Left, Down, Let go, Up, Right, Down, Grab, Up, Right, Down, Let go

- 절차지향: C
- 객체지향: Java
- 각 소프트웨어 개발 패러다임 사이의 차이 정리 및 발표
