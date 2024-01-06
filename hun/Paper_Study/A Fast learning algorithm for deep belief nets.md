저자 : Geoffrey E. Hinton and Simon Osindero

# Abstract
- hidden layer가 많고 densely-connected belief nets에서 추론을 어렵게 만드는 설명 효과를 제거하기 위해 "complementary priors"를 사용하는 방법을 보여준다.
- "complementary priors"를 사용하면 두 layer가 undirected associative memory를 형성하는 경우, 더 빠르고 greedy한 알고리즘을 도출할 수 있다.

### DBN(Deep Belief Network) & RBM(Restricted Boltzmann Machine)
#### RBM
- RBM은 Generative Model로 ANN, DNN, CNN, RNN 과 같은 Deterministic Model들과 다른 목표를 가짐.
- Deterministic Model들이 타겟과 가설 간의 차이를 줄여서 오차를 줄이는 것이 목표라고 한다면, Generative Model들의 목표는 확률밀도함수를 모델링하는 것이다.
- Boltzmann Machine이 가정한 것은 "우리가 보고 있는 것들 외에도 보이지 않는 요소들까지 잘 포함시켜 학습할 수 있다면 확률분포를 좀 더 정확하게 알 수 있지 않을까?"라는 것이다.
- <img src = "Pasted image 20240105220348.png">
- 노란색은 hidden unit, 초록색은 visible unit.
- RBM은 Boltzmann Machine에서부터 파생되어 나온 것으로 visible unit과 hidden unit에는 내부적인 연결이 없고, visible unit과 hidden unit 간의 연결만이 남아있는 형태이다.
- 우선은 visible, hidden layer의 node 간의 내부적인 연결이 없어진 것은 사건 간의 독립성을 가정함으로써 확률분포의 결합을 쉽게 표현하기 위해서이다.
- 또, visible layer와 hidden layer만을 연결해줌으로써 visible layer의 데이터가 주어졌을 때 hidden layer의 데이터를 계산할 수 있도록 하거나 혹은 hidden layer의 데이터가 주어졌을 때 visible layer의 데이터를 계산할 수 있도록 하는 ‘조건부 확률’을 계산할 수 있게 하는 것이다.
- 즉, $p(h,v)$ 는 계산하기 어렵지만, $p(h|v)$ 나 $p(v|h)$ 는 계산이 수월하기 때문이다.
- 더 자세한 내용 : https://angeloyeo.github.io/2020/10/02/RBM.html

#### DBN
- 입력층과 은닉층으로 구성된 RBM을 블록처럼 여러 층으로 쌓인 형태로 연결된 신경망
- 피드포워드 신경망에서 경사감소 소멸문제를 해결하기 위해 등장
- 특징
	- 비지도학습
	- 데이터가 충분하지 않을 때 유용
	- 겹층 RBM
- <img src="Pasted image 20240105221225.png">

# Introduction
