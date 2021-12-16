pipeline {
   agent {
    kubernetes {
      defaultContainer 'cgw-docker-builder'
      yaml '''
        apiVersion: v1
        kind: Pod
        spec:
          containers:
          - name: cgw-docker-builder
            image: docker.wdf.sap.corp:51021/com.sap.apigateway/cgw-docker-builder:1.11-20211215074523_958adf07f8b59b7ef9d04980bb0f4647c752f524
            command:
            - cat
            tty: true
        '''
    }
  }


	
  stages {
    stage('run script') {
      environment {
	    GITHUB_CREDENTIALS = credentials('centralcgwbot-github-tools-token')
	    }
      
      steps {
        sh './my_script.sh'
      }
    }
  }

}
