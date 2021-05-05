#include<iostream>
#include<queue>
#include<cmath>
#include<vector>
using namespace std;
int operatora[8]={1,2,3,0,0,0,1,2};//做某操作时传教士变化数量 
int operatorb[8]={0,0,0,1,2,3,1,1};//做某操作时野人变化数量 
int m,n;
int depth[4][4][2];
bool vis[4][4][2]={false};
struct state{
	int al,bl,b;
	bool operator==(const state& s2){
		if(this->al==s2.al&&this->bl==s2.bl&&this->b==s2.b) return true;
		else return false;
	}
	bool operator!=(const state& s2){
		if(this->al!=s2.al||this->bl==s2.bl||this->b==s2.b) return true;
		else return false;
	}
};
state father[4][4][2];
vector<state> closed;
vector<state> ans;
bool isclosed(state s){
	for(int i=0;i<closed.size();i++){
		if(closed[i]==s) return true;
	}
	return false;
}
bool ok(state s,int a,int b){
	if(s.b==1){ 
		if(s.al>=a&&s.bl>=b&&(((m-s.al)+a)>=((n-s.bl)+b)||((m-s.al)+a)==0||((n-s.bl)+b)==0)&&((s.al-a)>=(s.bl-b)||(s.al-a)==0||(s.bl-b)==0)) return true;
	}
	else{
		if((m-s.al)>=a&&(n-s.bl)>=b&&((s.al+a)>=(s.bl+b)||(s.al+a)==0||(s.bl+b)==0)&&(((m-s.al)-a)>=((n-s.bl)-b)||((m-s.al)-a)==0||((n-s.bl)-b)==0)) return true;
	}
	return false;
}
int main(){
	cin>>m>>n;
	state s,end;
	s.al=m;s.bl=n;s.b=1; 
	end.al=0;end.bl=0;end.b=0;
	depth[m][n][1]=0;vis[m][n][1]=true;
	struct cmp
    {
	    bool operator()(const state &s1,const state &s2)
    	{
     		int g1=depth[s1.al][s1.bl][s1.b];
        	int h1=s1.al+s1.bl;
          	int g2=depth[s2.al][s2.bl][s2.b];
        	int h2=s2.al+s2.bl;
    		return (g1+h1)<(g2+h2);
      	}	
    };
	priority_queue<state,vector<state>, cmp> q;
	q.push(s);
	while(!q.empty()){
		state top=q.top();
		q.pop();
		closed.push_back(top);
		if(top==end) break;
		for(int i=0;i<8;i++){
			if(ok(top,operatora[i],operatorb[i])){
				state now;
	      		if(top.b==1){   
		    		now.al=top.al-operatora[i];
		    		now.bl=top.bl-operatorb[i];
		    		now.b=0;
		    	}
		    	else{
			    	now.al=top.al+operatora[i];
		    		now.bl=top.bl+operatorb[i];
		    		now.b=1;
		    	} 
		    	if(vis[now.al][now.bl][now.b]){
		    		if(isclosed(now)) continue;//在close表内，不需要再次遍历 
		    		else{//在open表内，算算是否需要更新 
		    			if(depth[now.al][now.bl][now.b]>(depth[top.al][top.bl][top.b]+1)){
		    				depth[now.al][now.bl][now.b]=(depth[top.al][top.bl][top.b]+1);
		    				father[now.al][now.bl][now.b]=top;
						}
					}
				}
				else{//没被访问过 
					depth[now.al][now.bl][now.b]=depth[top.al][top.bl][top.b]+1;
					father[now.al][now.bl][now.b]=top;
					q.push(now);
					vis[now.al][now.bl][now.b]=true;
				}
			}
		}
	}
	while(end.al!=s.al||end.bl!=s.bl||end.b!=s.b){
		ans.push_back(end);
		end=father[end.al][end.bl][end.b];
	}
	ans.push_back(s);
	for(int i=ans.size()-1;i>=0;i--) printf("(%d,%d,%d)%s",ans[i].al,ans[i].bl,ans[i].b,i==0?"\n":"->");
	return 0;
}
