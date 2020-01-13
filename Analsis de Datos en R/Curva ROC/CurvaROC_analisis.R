library(knitr)
library(ROCR)
library(e1071)
library(caTools)
library(nnet)
library(scales)
set.seed(222)
#Cargara la base de datos al entorno de R
datos=read.csv("datos.csv",header=TRUE,sep=",")
datos$Temperatura=ifelse(datos$Temperatura>15,1,0)#
datos$Temperatura=as.factor(datos$Temperatura)
str(datos)
indice=sample(1:nrow(datos),size = 0.8*nrow(datos))
training=datos[indice,]
test=datos[-indice,]
library(randomForest)
#MODELo random forest
rf_model=randomForest(Temperatura~.,data =training)
rf_prediction=predict(rf_model,test,type='vote')
#modelo de regresion lineal
#lr_model=glm(PH~.,data=training,family = "binomial")
#lr_pred=prediction(lr_model,tes,type="response")
#curvas roc
library(pROC)
ROC_rf = roc(test$Temperatura,rf_prediction[,2])
#ROC_lr <- roc(test$PH, lr_prediction)
plot(ROC_rf)

