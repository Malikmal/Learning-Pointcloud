import sklearn
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import VotingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
#Load data
X,y=make_moons(n_samples=500,noise=0.30,random_state=42)
#Split test and train data
X_train,X_test,y_train,y_test=train_test_split(X,y,random_state=42)

log_clf = LogisticRegression(solver="lbfgs",random_state=42)
rnd_clf = RandomForestClassifier(n_estimators=100, random_state=42)
svm_clf = SVC(gamma="scale", random_state=42, probability=True)

#keras Model
def build_nn():
    model=Sequential([
        Dense(50,activation='relu', input_shape=[2]),
        Dense(1, activation='sigmoid')
    ])
    model.compile(
        optimizer='Adam',
        loss='binary_crossentropy',
        metrics=['accuracy']
    )
    return model

keras_clf = tf.keras.wrappers.scikit_learn.KerasClassifier(
    build_nn,
    epochs=500,
    verbose=False
)

keras_clf._estimator_type="classifier"
#https://stackoverflow.com/questions/59897096/votingclassifier-with-pipelines-as-estimators/59915844#59915844


voting = VotingClassifier(
    estimators=[
        ('lr', log_clf),
        ('rf', rnd_clf),
        ('svc',svm_clf),
        ('keras','keras_clf')
    ],
    voting='soft',
    flatten_transform=True
)

voting.fit(X_train, y_train)

for clf in (log_clf, rnd_clf, svm_clf, keras_clf, voting):
    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    print(clf.__class__.__name__, accuracy_score(y_test, y_pred))

