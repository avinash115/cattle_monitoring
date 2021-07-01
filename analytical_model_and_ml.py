#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
data = pd.read_csv("C:/Users/Avinash/Desktop/Datafromsensor.csv")
data

data['VeDBA']=np.sqrt((data['X']*data['X'])+(data['Y']*data['Y'])+(data['Z']*data['Z']))
g=9.8
data['SCAY']=g-np.cos(60)
data['Hum']= ((data['H'])/100);
data['THI']=(0.8*data['T'])+((data['Hum'])*(data['T']-14.4))+46.4
data
data['Mean_VeDBA']=data['VeDBA'].mean()
data['Mean_SCAY']=data['SCAY'].mean()
Threshold_A=0.0413
Threshold_B=0.055
data
Activity=[]
for i,j in zip(data.Mean_VeDBA , data.Mean_SCAY):
     if(i>Threshold_A):
        Activity.append('Feeding')
    else: 
        if(j>Threshold_B):
            Activity.append('Standing')
        else:
            Activity.append('Lying')

data['Activity']=Activity
Heat_stress =[]
for k in data.THI:
    if(72<=k<=89):
        Heat_stress.append('Mild')
    elif(80<=k<=89):
        Heat_stress.append('Moderate')
    elif(k>=90):
        Heat_stress.append('Severe')
    else:
        Heat_stress.append('Normal')
        
data['Heat_stress']=Heat_stress
data


# In[ ]:


#Plotting graphs
fig= plt.figure(figsize=(20,3))
plt.plot(data['Time'],data['X'],color='red')
plt.plot(data['Time'],data['Y'],color='blue')
plt.plot(data['Time'],data['Z'],color='green')
plt.xticks(rotation=90)
plt.xlabel('Time')
plt.ylabel("Acceleration")
plt.legend(['X','Y','Z'])
plt.show()

fig= plt.figure(figsize=(20,2))
plt.plot(data['Time'],data['THI'],color='red')
plt.xticks(rotation=90)
plt.xlabel('Time')
plt.ylabel("THI")
plt.legend(['THI'])
plt.show()


# In[ ]:


#Machine learning
from sklearn.preprocessing import LabelEncoder,OneHotEncoder
le=LabelEncoder()
data['Activity_label']=le.fit_transform(data['Activity'])
data

x=data.iloc[:,[2,3,4]].values
y=data.iloc[:,9].values
display(x,y)

from sklearn.preprocessing import StandardScaler
sc_x=StandardScaler()
x=sc_x.fit_transform(x)
x

from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
classifier=DecisionTreeClassifier(criterion="entropy",random_state=0)
X_train,X_test,Y_train,Y_test=train_test_split(x,y,test_size=0.2,random_state=0)
classifier.fit(X_train,Y_train)
y_pred=classifier.predict(X_test)

from sklearn.metrics import confusion_matrix
cm=confusion_matrix(Y_test,y_pred)
cm

print(accuracy_score(y_pred,Y_test))

