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
- 데이터 벡터가 주어졌을 때 숨겨진 활동의 조건부 분포를 추론하기 어렵기 때문에 hidden layer가 많은 조밀하게 연결된 방향성 신뢰 네트워크에서는 학습이 어렵다. 
- Variational methods : 실제 조건부 분포에 대한 근사치를 사용. but, 사전 분포가 독립성을 가정하는 가장 깊은 hidden layer에서는 근사치가 좋지 않을 수 있다.
- Variational learning : 모든 매개변수를 학습해야 하며 매개변수 수가 증가함에 따라 학습 시간 규모가 제대로 설정되지 않을 수 있다.
- 그래서 이 논문에서는 새로운 모델을 설명하려고 함.
	- 상위 두 개의 hidden layer가 undirected associative memory를 형성.
	- 나머지 hidden layer가 directed acyclic graph를 형성.(이미지의 픽셀과 같은 관찰 가능한 변수로 변환)
- 이 모델의 특징
	1. 수백만의 매개변수와 hidden layer가 있어도 좋은 매개변수 세트를 빠르게 찾을 수 있는 빠르고 greedy한 algorithm이 있다.
	2. 비지도 방식이지만, 레이블과 데이터를 모드 생성하는 모델을 학습해 레이블이 지정된 데이터에도 적용할 수 있다.
	3. MNIST에서 우수한 성과가 있는 미세 조정 알고리즘이 있다.
	4. 생성모델을 사용하면 깊은 hidden layer의 분산 표현을 쉽게 해석할 수 있다.
	5. 지각을 형성하는데 필요한 추론은 빠르고 정확하다.
	6. 학습 알고리즘은 지역적으로, 시냅스 강도 조정은 시냅스 전, 후의 상태에만 의존한다.
	7. 통신이 간단하다. 뉴런은 확률론적 이진 상태만 전달하면 된다.

- 이후 섹션에 대해 소개함.
- section 2 
	- 지향 모델에서 추론을 어렵게 만드는 보완적 사전 개념(idea of complementary prior)을 소개한다. 
	- 상호보완적인 사전확률을 갖는 direct belief network의 예가 제시됨.
- section 3 
	- RBM와 가중치가 묶인 무한 directed network간의 동등성을 보여준다.
- section 4 
	- 한번에 한 레이어씩 다층 지향 네트워크를 구성하기 위한 빠르고 greedy한 알고리즘을 소개한다. 
	- variational bound를 사용하면 각 새로운 레이터가 추가될 때 전체 생성 모델이 향상된다는 것을 알 수 있다. 
	- greedy 알고리즘은 동일한 "약한" 학습기를 반복적으로 사용하는 부스팅과 어느 정도 유사, 다음 단계에서 새로운 것을 학습할 수 있도록 각 데이터 벡터에 다시 가중치를 부여하는 대신 이를 다시 나타냄.(?)
	- Deep Directed Net을 구성하는 데 사용되는 "약한" 학습기는 그 자체가 undirected graphical 모델임.(?)
- section 5 
	- Fast Greedy 알고리즘에 의해 생성된 가중치가 up-down 알고리즘을 사용해 미세 조정될 수 있는 방법을 보여준다.
- section 6 
	- MNIST에서 성능 비교
	- support vector machines에서 성능 비교
- section 7 
	- 시각적 입력 제약 없이 네트워크가 실행될 때 네트워크가 어떻게 동작하는지 설명한다.
- + 이 논문에서는 확률론적 이진 변수로 구성된 네트워크를 고려할 것이지만 변수의 로그 확률이 직접 연결된 이웃 상태의 추가 함수인 다른 모델로 아이디어를 일반화할 수 있다고 한다.

# Complementary priors
- Figure 2(Explaining away효과)
	- <img src="Pasted image 20240118172340.png">
	- C : 암에 걸림, H : 두통 있음, B : 멍이 듦.
	- $P(C|H)$ : 두통이 있을 때 암에 걸렸을 확률 = 0.5525
	- $P(C|H, B)$ : 두통과 멍이 있을 때 암에 결렸을 확률 = 0.112
	- 이 상황에서 두통이 있으면 암에 걸렸을 확률이 55.25%이다. 그런데 거울을 보고 멍이 들었음을 알게 되었다면 암에 걸렸을 확률이 11.2%로 감소한다.
	- 멍이 들었다.(B)라는 사건은 두통이 '암' 이 아니라 '싸움'이라는 또 다른 원인으로 인해 발생했을 수 있다는 사실을 설명하기 때문이다.
	- 이와 같이 Explaining away 효과가 발생할 경우 서로 독립인 변수 '싸움'과 '암'이 서로 영향을 미치기 때문에 추론이 어려워진다.
- directed belief nets에서 Explaining away 현상은 추론을 어렵게 만든다.
- 조밀하게 연결된 네트워크에서 hidden variable에 대한 posterior distribution(사후 분포)는 혼합 모델이나 additive Gaussian noise가 있는 선형 모델을 제외하고는 다루기 어렵다.
- MCMC(Markov Chain Monte Carlo)방법을 사용해 후방에서 샘플링할 수 있지만 시간이 오래 걸린다.
	- MCMC(Markov Chain Monte Carlo) : 
		- Markov Chain을 이용한 Monte Carlo 방법.
		- Monte Carlo : 수식만으로는 계산하기 어려운 문제가 있을 때 랜덤 샘플을 얻은 뒤 그 랜덤 샘플을 이용해서 함수의 값을 확률적으로 계산하는 방법이다.
		- Markov Chain : 미래 확률이 과거 확률에 독립이며 오로지 직전 시점의 확률에만 의존한다는 것이 핵심이다. 즉, 한 상태에서 다른 상태로의 전이(transition)은 그동안의 전이 확률(**Transition Probability**)을 필요로 하지 않고 바로 직전의 전이 확률로 추정할 수 있다는 얘기이다.
		- MCMC : MCMC는 우리가 샘플을 얻고자 하는 목표 분포인 Stationary distribution으로부터 랜덤 샘플을 얻는 방법
	- https://m.blog.naver.com/jinis_stat/221687056797
- Variational methods(Neal and Hinton, 1998)은 실제 사후를 근사화하며 훈련 데이터의 로그 확률에 대한 하한을 향상시키는데 사용할 수 있다. hidden state에 대한 추론이 잘못 수행된 경우에도 학습이 변이 범위를 개선한다는 장점이 있지만, hidden variable이 있는 모델에서도 설명을 완전히 제거하는 방법을 찾는 것이 낫다. 그런데 이는 불가능하다는 것이 널리 알려져 있다.

- Logistic belief net :
	- 
