//Louay Farah
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define pb push_back
#define mp make_pair
#define endl "\n"
#define fi first
#define se second
 
const int nx[4] = {0, 0, 1, -1};
const int ny[4] = {1, -1, 0, 0};
 
//Disjoint Set Union implementation
//This data structure will be used to check whether some states are disjoint or not
struct dsu
{
    vector<int> link;
    vector<int> len;
    ll comps;
 
    void init(int n)
    {
        link.assign(n+1, 0);
        len.assign(n+1, 0);
 
        for(int i = 1; i<=n; i++)
        {
            link[i] = i;
            len[i] = 1;
        }
 
        comps = n;
    }
 
    //Find the representative of u
    int find(int u)
    {
        if(u!=link[u])
            link[u] = find(link[u]);
        return link[u];
    }
 
    //check whether u and v have the same representative or not
    bool check(int u, int v)
    {
        return find(u)==find(v);
    }
 
    //Unite two nodes u and v
    void unite(int u, int v)
    {
        u = find(u);
        v = find(v);
 
        if(u==v)
            return;
 
        comps--;
        if(len[u]<len[v])
            swap(u, v);
        len[u]+=len[v];
        link[v] = u;
    }
};
 
 
//Function to check whether a state is valid or not (consists only of numbers and latin letters)
bool state_is_valid(string state)
{
    for(auto c: state)
    {
        if(!((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9')))
            return false;
    }
 
    return true;
}
 
//Function to check whether an alphabet element is valid or not (consists only of numbers, latin letters, and undersocore '_')
bool name_is_valid(string name)
{
    for(auto c: name)
    {
        if(!((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')||(c >= '0' && c <= '9')||(c == '_')))
            return false;
    }
 
    return true;
}
 
 
int main()
{
    freopen("input.txt", "r", stdin);
 
    //BSTs to check the inclusivity of s/a
    set<string> states, alphabet, final_states;
    //Dynamic arrays to store the initial state and final states
    vector<string> initial_state;
    //To store the transitions: s1>a>s2 becomes mp(mp(s1, s2), a)
    vector<pair<pair<string, string>, string>> transitions;
 
    //input states
    string s;
    cin >> s;
 
    if(int(s.length()) < 8)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    //extract states
    ll i = 8;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        states.insert(curr);
        i++;
    }
 
    if(states.empty())
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    for(auto state: states)
    {
        if(!state_is_valid(state))
        {
 
            cout << "E1: Input file is malformed" << endl;
            return 0;
        }
    }
 
    //input alphabet
    cin >> s;
 
    if(int(s.length()) < 7)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    //extract alphabet
    i = 7;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        alphabet.insert(curr);
        i++;
    }
 
    if(alphabet.empty())
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    for(auto name: alphabet)
    {
        if(!name_is_valid(name))
        {
 
            cout << "E1: Input file is malformed" << endl;
            return 0;
        }
    }
 
    //input initial state(s)
    cin >> s;
 
    if(int(s.length()) < 9)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    //extract initial state(s)
    i = 9;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        initial_state.pb(curr);
        i++;
    }
 
    if(int(initial_state.size()) > 1) //If more than one initial state
    {
 
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    if(initial_state.empty()) //If no initial states
    {
 
        cout << "E2: Initial state is not defined" << endl;
        return 0;
    }
 
    if(states.count(initial_state[0]) == 0) //If the initial state does not belong to states
    {
        cout << "E4: A state '" << initial_state[0] << "' is not in the set of states" << endl;
        return 0;
    }
 
    //input final state(s)
    cin >> s;
 
    if(int(s.length()) < 11)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    //extract final state(s)
    i = 11;
    while(i < int(s.length())-1)
    {
        string curr = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            curr.pb(s[i]);
            i++;
        }
        final_states.insert(curr);
        i++;
    }
 
    if(final_states.empty()) //If there are no final states
    {
        cout << "E3: Set of accepting states is empty" << endl;
        return 0;
    }
 
    for(auto state: final_states)
    {
        if(states.count(state) == 0) //If the current final state does not belong to states
        {
 
            cout << "E4: A state '" << state << "' is not in the set of states" << endl;
            return 0;
        }
    }
 
    //input transitions
    cin >> s;
 
    if(int(s.length()) < 7)
    {
        cout << "E1: Input file is malformed" << endl;
        return 0;
    }
 
    //extract transitions
    i = 7;
    while(i < int(s.length())-1)
    {
        string a = "", b = "", w = "";
        while(i < int(s.length())-1)
        {
            if(s[i] == '>')
                break;
            a.pb(s[i]);
            i++;
        }
        i++;
 
        while(i < int(s.length())-1)
        {
            if(s[i] == '>')
                break;
            w.pb(s[i]);
            i++;
        }
        i++;
 
        while(i < int(s.length())-1)
        {
            if(s[i] == ',')
                break;
            b.pb(s[i]);
            i++;
        }
        i++;
 
        if(states.count(a) == 0)
        {
 
            cout << "E4: A state '" << a << "' is not in the set of states" << endl;
            return 0;
        }
 
        if(states.count(b) == 0)
        {
 
            cout << "E4: A state '" << b << "' is not in the set of states" << endl;
            return 0;
        }
 
        if(alphabet.count(w) == 0)
        {
 
            cout << "E5: A transition '" << w << "' is not represented in the alphabet" << endl;
            return 0;
        }
 
        transitions.pb(mp(mp(a, b), w));
    }
 
    dsu d;
    d.init(int(states.size()));
 
    //Hash every state to a unique number for usage in dsu
    map<string, ll> m;
    ll counter = 1;
    for(auto state: states)
    {
        m[state] = counter++;
    }
 
    ll nb_states = int(states.size());
 
    //Adjacency list
    vector<pair<ll, string>> adj[nb_states+1];
 
    //Build the adjacency list
    for(auto p: transitions)
    {
        adj[m[p.fi.fi]].pb(mp(m[p.fi.se], p.se));
    }
 
    //unite the states
    for(int u = 1; u<=nb_states; u++)
    {
        for(auto v: adj[u])
        {
            d.unite(u, v.fi);
        }
    }
 
    if(d.comps != 1) //If some states are disjoint
    {
 
        cout << "E6: Some states are disjoint" << endl;
        return 0;
    }
 
    //Set to store unique transitions. i.e. if the fsa is non-deterministic
    set<pair<string, string>> unique_transitions;
    for(auto p: transitions)
    {
        unique_transitions.insert(mp(p.fi.fi, p.se));
    }
 
    if(unique_transitions.size() != transitions.size()) //If the fsa is non-deterministic
    {
        cout << "E7: FSA is nondeterministic" << endl;
        return 0;
    }
 
    int nbStates = int(states.size());
 
    //Kleene's Algorithm implementation
 
    //Step 1: initialization of R
    map<pair<string, string>, string> currR;
    for(int i = 0; i<nbStates; i++)
    {
        for(int j = 0; j<nbStates; j++)
        {
            currR[mp(*next(states.begin(), i), *next(states.begin(), j))] = "({})";
        }
    }
 
    //Step 2: Calculation the initial regular expressions for k = -1
    map<pair<string, string>, vector<string>> combs;
    for(auto tr: transitions)
    {
        string a = tr.fi.fi, b = tr.fi.se, w = tr.se;
        combs[mp(a, b)].pb(w);
    }
 
    for(int i = 0; i<nbStates; i++)
    {
        for(int j = 0; j<nbStates; j++)
        {
            sort(combs[mp(*next(states.begin(), i), *next(states.begin(), j))].begin(), combs[mp(*next(states.begin(), i), *next(states.begin(), j))].end());
        }
    }
 
    for(int i = 0; i<nbStates; i++)
    {
        for(int j = 0; j<nbStates; j++)
        {
            string a = *next(states.begin(), i), b = *next(states.begin(), j);
            string temp = "({})";
 
            if(!combs[mp(a, b)].empty())
            {
                temp = "(";
                for(auto w: combs[mp(a, b)])
                {
                    temp += w;
                    temp += "|";
                }
                temp.pop_back();
                if(a == b)
                    temp += "|eps";
                temp += ")";
            }
            else if(a == b)
            {
                temp = "(eps)";
            }
 
            currR[mp(a, b)] = temp;
        }
    }
 
    //Step 3: Calculating each regular expressions from the previous one for k = 0, 1, ..., nbStates
    for(int step = 0; step < nbStates; step++)
    {
        map<pair<string, string>, string> newR;
        for(int i = 0; i<nbStates; i++)
        {
            for(int j = 0; j<nbStates; j++)
            {
                newR[mp(*next(states.begin(), i), *next(states.begin(), j))] = "{}";
            }
        }
 
        for(int i = 0; i<nbStates; i++)
        {
            for(int j = 0; j<nbStates; j++)
            {
                string res = "";
 
                res += "(";
 
                res += currR[mp(*next(states.begin(), i), *next(states.begin(), step))];
 
                res += currR[mp(*next(states.begin(), step), *next(states.begin(), step))];
 
                res += "*";
 
                res += currR[mp(*next(states.begin(), step), *next(states.begin(), j))];
 
                res += "|";
 
                res += currR[mp(*next(states.begin(), i), *next(states.begin(), j))];
 
                res += ")";
 
                newR[mp(*next(states.begin(), i), *next(states.begin(), j))] = res;
            }
        }
 
        currR = newR;
    }
 
 
    //Step 4: Building the resulting regular expression
    string res = "";
 
    //We concatenate the regular expressions for all the accepting states, separating them with the '|' symbol
    for(int i = 0; i<nbStates; i++)
    {
        if(final_states.count(*next(states.begin(), i)) == 0)
            continue;
 
 
        res += currR[mp(initial_state[0], *next(states.begin(), i))];
        res += "|";
    }
 
    if(res[int(res.length())-1] == '|')
        res.pop_back();
 
    //Printing the resulting regular expression
    cout << res << endl;
 
    return 0;
}