
  
  

  


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="chrome=1">
        <title>4sem/burgonskiy/rsa.c at master from kmi9work's msiu - GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="http://github.com/fluidicon.png" title="GitHub" />

    <link href="http://assets3.github.com/stylesheets/bundle_common.css?afe70a1758c8408acd5e2f57bc6c24febb8ca721" media="screen" rel="stylesheet" type="text/css" />
<link href="http://assets3.github.com/stylesheets/bundle_github.css?afe70a1758c8408acd5e2f57bc6c24febb8ca721" media="screen" rel="stylesheet" type="text/css" />

    <script type="text/javascript" charset="utf-8">
      var GitHub = {}
      var github_user = 'kmi9work'
      
    </script>
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js" type="text/javascript"></script>
    <script src="http://assets1.github.com/javascripts/bundle_common.js?afe70a1758c8408acd5e2f57bc6c24febb8ca721" type="text/javascript"></script>
<script src="http://assets2.github.com/javascripts/bundle_github.js?afe70a1758c8408acd5e2f57bc6c24febb8ca721" type="text/javascript"></script>

        <script type="text/javascript" charset="utf-8">
      GitHub.spy({
        repo: "kmi9work/msiu"
      })
    </script>

    
  
    
  

  <link href="http://github.com/kmi9work/msiu/commits/master.atom" rel="alternate" title="Recent Commits to msiu:master" type="application/atom+xml" />

        <meta name="description" content="kmi9 work in msiu" />
    <script type="text/javascript">
      GitHub.nameWithOwner = GitHub.nameWithOwner || "kmi9work/msiu";
      GitHub.currentRef = "master";
    </script>
  

            <script type="text/javascript">
      var _gaq = _gaq || [];
      _gaq.push(['_setAccount', 'UA-3769691-2']);
      _gaq.push(['_trackPageview']);
      (function() {
        var ga = document.createElement('script');
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        ga.setAttribute('async', 'true');
        document.documentElement.firstChild.appendChild(ga);
      })();
    </script>

  </head>

  

  <body>
    

    
      <script type="text/javascript">
        var _kmq = _kmq || [];
        (function(){function _kms(u,d){if(navigator.appName.indexOf("Microsoft")==0 && d)document.write("<scr"+"ipt defer='defer' async='true' src='"+u+"'></scr"+"ipt>");else{var s=document.createElement('script');s.type='text/javascript';s.async=true;s.src=u;(document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(s);}}_kms('https://i.kissmetrics.com/i.js');_kms('http'+('https:'==document.location.protocol ? 's://s3.amazonaws.com/' : '://')+'scripts.kissmetrics.com/406e8bf3a2b8846ead55afb3cfaf6664523e3a54.1.js',1);})();
      </script>
    

    

    

    <div class="subnavd" id="main">
      <div id="header" class="pageheaded">
        <div class="site">
          <div class="logo">
            <a href="https://github.com/"><img src="/images/modules/header/logov3.png" alt="github" /></a>
          </div>
          
            






  
    <div class="userbox">
      <div class="inner">
        <div class="avatarname">
          <a href="http://github.com/kmi9work"><img src="http://www.gravatar.com/avatar/60f6b4d92273b08de6fe09ac0e2db4cc?s=140&d=http%3A%2F%2Fgithub.com%2Fimages%2Fgravatars%2Fgravatar-140.png" alt="" width="20" height="20"  /></a>
          <a href="http://github.com/kmi9work" class="name">kmi9work</a>

          
          
        </div>
        <ul class="usernav">
          <li><a href="https://github.com/">Dashboard</a></li>
          <li>
            
            <a href="https://github.com/inbox">Inbox</a>
            <a href="https://github.com/inbox" class="unread_count ">0</a>
          </li>
          <li><a href="https://github.com/account">Account Settings</a></li>
                    <li><a href="/logout">Log Out</a></li>
        </ul>
      </div>
    </div><!-- /.userbox -->
  


          
          <div class="topsearch">
  
    <form action="/search" id="top_search_form" method="get">
      <a href="/search" class="advanced-search tooltipped downwards" title="Advanced Search">Advanced Search</a>
      <input type="search" class="search my_repos_autocompleter" name="q" results="5" placeholder="Search&hellip;" /> <input type="submit" value="Search" class="button" />
      <input type="hidden" name="type" value="Everything" />
      <input type="hidden" name="repo" value="" />
      <input type="hidden" name="langOverride" value="" />
      <input type="hidden" name="start_value" value="1" />
    </form>
  
  
    <ul class="nav">
      <li><a href="/explore">Explore GitHub</a></li>
      <li><a href="http://gist.github.com">Gist</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="http://help.github.com">Help</a></li>
    </ul>
  
</div>

        </div>
      </div>

      
      
        
    <div class="site">
      <div class="pagehead repohead vis-public   ">
        <h1>
          <a href="/kmi9work">kmi9work</a> / <strong><a href="http://github.com/kmi9work/msiu">msiu</a></strong>
          
          
        </h1>

        
    <ul class="actions">
      

      
        <li class="for-owner" style="display:none"><a href="https://github.com/kmi9work/msiu/edit" class="minibutton btn-admin "><span><span class="icon"></span>Admin</span></a></li>
        <li>
          <a href="/kmi9work/msiu/toggle_watch" class="minibutton btn-watch " id="watch_button" style="display:none"><span><span class="icon"></span>Watch</span></a>
          <a href="/kmi9work/msiu/toggle_watch" class="minibutton btn-watch " id="unwatch_button" style="display:none"><span><span class="icon"></span>Unwatch</span></a>
        </li>
        
          
            <li class="for-notforked" style="display:none"><a href="/kmi9work/msiu/fork" class="minibutton btn-fork " id="fork_button" onclick="var f = document.createElement('form'); f.style.display = 'none'; this.parentNode.appendChild(f); f.method = 'POST'; f.action = this.href;var s = document.createElement('input'); s.setAttribute('type', 'hidden'); s.setAttribute('name', 'authenticity_token'); s.setAttribute('value', 'd51e9c89c18a23268a7690251710925dec01091e'); f.appendChild(s);f.submit();return false;"><span><span class="icon"></span>Fork</span></a></li>
            <li class="for-hasfork" style="display:none"><a href="#" class="minibutton btn-fork " id="your_fork_button"><span><span class="icon"></span>Your Fork</span></a></li>
          

          
          <li id="pull_request_item" class='ospr' style="display:none"><a href="/kmi9work/msiu/pull_request/" class="minibutton btn-pull-request "><span><span class="icon"></span>Pull Request</span></a></li>
          

          <li><a href="#" class="minibutton btn-download " id="download_button"><span><span class="icon"></span>Download Source</span></a></li>
        
      
      
      <li class="repostats">
        <ul class="repo-stats">
          <li class="watchers"><a href="/kmi9work/msiu/watchers" title="Watchers" class="tooltipped downwards">1</a></li>
          <li class="forks"><a href="/kmi9work/msiu/network" title="Forks" class="tooltipped downwards">1</a></li>
        </ul>
      </li>
    </ul>


        
  <ul class="tabs">
    <li><a href="http://github.com/kmi9work/msiu/tree/master" class="selected" highlight="repo_source">Source</a></li>
    <li><a href="http://github.com/kmi9work/msiu/commits/master" highlight="repo_commits">Commits</a></li>

    
    <li><a href="/kmi9work/msiu/network" highlight="repo_network">Network (1)</a></li>

    
      <li><a href="/kmi9work/msiu/forkqueue" highlight="repo_fork_queue">Fork Queue</a></li>
    

    
      
      <li><a href="/kmi9work/msiu/issues" highlight="issues">Issues (0)</a></li>
    

    
      
      <li><a href="/kmi9work/msiu/downloads">Downloads (0)</a></li>
    

    
      
      <li><a href="http://wiki.github.com/kmi9work/msiu/">Wiki (1)</a></li>
    

    <li><a href="/kmi9work/msiu/graphs" highlight="repo_graphs">Graphs</a></li>

    <li class="contextswitch nochoices">
      <span class="toggle leftwards" >
        <em>Branch:</em>
        <code>master</code>
      </span>
    </li>
  </ul>

  <div style="display:none" id="pl-description"><p><em class="placeholder">click here to add a description</em></p></div>
  <div style="display:none" id="pl-homepage"><p><em class="placeholder">click here to add a homepage</em></p></div>

  <div class="subnav-bar">
  
  <ul>
    <li>
      <a href="#" class="dropdown">Switch Branches (2)</a>
      <ul>
        
          
            <li><strong>master &#x2713;</strong></li>
            
          
          
            <li><a href="/kmi9work/msiu/blob/work/4sem/burgonskiy/rsa.c" action="show">work</a></li>
          
        
      </ul>
    </li>
    <li>
      <a href="#" class="dropdown defunct">Switch Tags (0)</a>
      
    </li>
    <li>
    
    <a href="/kmi9work/msiu/branches" class="manage">Branch List</a>
    
    </li>
  </ul>
</div>

  
  
  
  
  


        
    <div id="repo_details" class="metabox clearfix">
      <div id="repo_details_loader" class="metabox-loader" style="display:none">Sending Request&hellip;</div>

      

      <div id="repository_description" rel="repository_description_edit">
        
          <p>kmi9 work in msiu
            <span id="read_more" style="display:none">&mdash; <a href="#readme">Read more</a></span>
          </p>
        
      </div>
      <div id="repository_description_edit" style="display:none;" class="inline-edit">
        <form action="/kmi9work/msiu/edit/update" method="post"><div style="margin:0;padding:0"><input name="authenticity_token" type="hidden" value="d51e9c89c18a23268a7690251710925dec01091e" /></div>
          <input type="hidden" name="field" value="repository_description">
          <input type="text" class="textfield" name="value" value="kmi9 work in msiu">
          <div class="form-actions">
            <button class="minibutton"><span>Save</span></button> &nbsp; <a href="#" class="cancel">Cancel</a>
          </div>
        </form>
      </div>

      
      <div class="repository-homepage" id="repository_homepage" rel="repository_homepage_edit">
        <p><a href="http://" rel="nofollow"></a></p>
      </div>
      <div id="repository_homepage_edit" style="display:none;" class="inline-edit">
        <form action="/kmi9work/msiu/edit/update" method="post"><div style="margin:0;padding:0"><input name="authenticity_token" type="hidden" value="d51e9c89c18a23268a7690251710925dec01091e" /></div>
          <input type="hidden" name="field" value="repository_homepage">
          <input type="text" class="textfield" name="value" value="">
          <div class="form-actions">
            <button class="minibutton"><span>Save</span></button> &nbsp; <a href="#" class="cancel">Cancel</a>
          </div>
        </form>
      </div>

      <div class="rule "></div>

      <div id="url_box" class="url-box">
        <ul class="clone-urls">
          
            
              <li id="private_clone_url"><a href="git@github.com:kmi9work/msiu.git" data-permissions="Read+Write">SSH</a></li>
            
            <li id="http_clone_url"><a href="https://kmi9work@github.com/kmi9work/msiu.git" data-permissions="Read+Write">HTTP</a></li>
            <li id="public_clone_url"><a href="git://github.com/kmi9work/msiu.git" data-permissions="Read-Only">Git Read-Only</a></li>
          
        </ul>
        <input type="text" spellcheck="false" id="url_field" class="url-field" />
              <span style="display:none" id="url_box_clippy"></span>
      <span id="clippy_tooltip_url_box_clippy" class="clippy-tooltip tooltipped" title="copy to clipboard">
      <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"
              width="14"
              height="14"
              class="clippy"
              id="clippy" >
      <param name="movie" value="http://assets1.github.com/flash/clippy.swf?v5"/>
      <param name="allowScriptAccess" value="always" />
      <param name="quality" value="high" />
      <param name="scale" value="noscale" />
      <param NAME="FlashVars" value="id=url_box_clippy&amp;copied=&amp;copyto=">
      <param name="bgcolor" value="#FFFFFF">
      <param name="wmode" value="opaque">
      <embed src="http://assets1.github.com/flash/clippy.swf?v5"
             width="14"
             height="14"
             name="clippy"
             quality="high"
             allowScriptAccess="always"
             type="application/x-shockwave-flash"
             pluginspage="http://www.macromedia.com/go/getflashplayer"
             FlashVars="id=url_box_clippy&amp;copied=&amp;copyto="
             bgcolor="#FFFFFF"
             wmode="opaque"
      />
      </object>
      </span>

        <p id="url_description">This URL has <strong>Read+Write</strong> access</p>
      </div>
    </div>


        

      </div><!-- /.pagehead -->

      









<script type="text/javascript">
  GitHub.currentCommitRef = "master"
  GitHub.currentRepoOwner = "kmi9work"
  GitHub.currentRepo = "msiu"
  GitHub.downloadRepo = '/kmi9work/msiu/archives/master'

  
    GitHub.hasWriteAccess = true
    GitHub.hasAdminAccess = true
    GitHub.watchingRepo = true
    GitHub.ignoredRepo = false
    GitHub.hasForkOfRepo = null
    GitHub.hasForked = true
  

  
</script>










  <div id="commit">
    <div class="group">
        
  <div class="envelope commit">
    <div class="human">
      
        <div class="message"><pre><a href="/kmi9work/msiu/commit/54e906046892b374a7be9bf7ba50d0b357b5a529">aero andre + a little</a> </pre></div>
      

      <div class="actor">
        <div class="gravatar">
          
          <img src="http://www.gravatar.com/avatar/ae691ef824eeb9af3815a3e005277c03?s=140&d=http%3A%2F%2Fgithub.com%2Fimages%2Fgravatars%2Fgravatar-140.png" alt="" width="30" height="30"  />
        </div>
        <div class="name">Михаил Костенчук <span>(author)</span></div>
        <div class="date">
          <abbr class="relatize" title="2010-06-07 01:47:05">Mon Jun 07 01:47:05 -0700 2010</abbr>
        </div>
      </div>

      

    </div>
    <div class="machine">
      <span>c</span>ommit&nbsp;&nbsp;<a href="/kmi9work/msiu/commit/54e906046892b374a7be9bf7ba50d0b357b5a529" hotkey="c">54e906046892b374a7be</a><br />
      <span>t</span>ree&nbsp;&nbsp;&nbsp;&nbsp;<a href="/kmi9work/msiu/tree/54e906046892b374a7be9bf7ba50d0b357b5a529" hotkey="t">faf9ab6c6ec52c3aa3a0</a><br />
      
        <span>p</span>arent&nbsp;
        
        <a href="/kmi9work/msiu/tree/8d7c36565abb834fa2c8d940b2b31c5aca44bb08" hotkey="p">8d7c36565abb834fa2c8</a>
      

    </div>
  </div>

    </div>
  </div>



  
    <div id="path">
      <b><a href="/kmi9work/msiu/tree/master">msiu</a></b> / <a href="/kmi9work/msiu/tree/master/4sem">4sem</a> / <a href="/kmi9work/msiu/tree/master/4sem/burgonskiy">burgonskiy</a> / rsa.c       <span style="display:none" id="clippy_4405">4sem/burgonskiy/rsa.c</span>
      
      <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"
              width="110"
              height="14"
              class="clippy"
              id="clippy" >
      <param name="movie" value="http://assets1.github.com/flash/clippy.swf?v5"/>
      <param name="allowScriptAccess" value="always" />
      <param name="quality" value="high" />
      <param name="scale" value="noscale" />
      <param NAME="FlashVars" value="id=clippy_4405&amp;copied=copied!&amp;copyto=copy to clipboard">
      <param name="bgcolor" value="#FFFFFF">
      <param name="wmode" value="opaque">
      <embed src="http://assets1.github.com/flash/clippy.swf?v5"
             width="110"
             height="14"
             name="clippy"
             quality="high"
             allowScriptAccess="always"
             type="application/x-shockwave-flash"
             pluginspage="http://www.macromedia.com/go/getflashplayer"
             FlashVars="id=clippy_4405&amp;copied=copied!&amp;copyto=copy to clipboard"
             bgcolor="#FFFFFF"
             wmode="opaque"
      />
      </object>
      

    </div>

    <div id="files">
      <div class="file">
        <div class="meta">
          <div class="info">
            <span class="icon"><img alt="Txt" height="16" src="http://assets2.github.com/images/icons/txt.png?afe70a1758c8408acd5e2f57bc6c24febb8ca721" width="16" /></span>
            <span class="mode" title="File Mode">100644</span>
            
              <span>158 lines (146 sloc)</span>
            
            <span>3.832 kb</span>
          </div>
          <ul class="actions">
            
              <li><a id="file-edit-link" href="#" rel="/kmi9work/msiu/file-edit/__ref__/4sem/burgonskiy/rsa.c">edit</a></li>
            
            <li><a href="/kmi9work/msiu/raw/master/4sem/burgonskiy/rsa.c" id="raw-url">raw</a></li>
            
              <li><a href="/kmi9work/msiu/blame/master/4sem/burgonskiy/rsa.c">blame</a></li>
            
            <li><a href="/kmi9work/msiu/commits/master/4sem/burgonskiy/rsa.c">history</a></li>
          </ul>
        </div>
        
  <div class="data syntax type-c">
    
      <table cellpadding="0" cellspacing="0">
        <tr>
          <td>
            <pre class="line_numbers"><span id="LID1" rel="#L1">1</span>
<span id="LID2" rel="#L2">2</span>
<span id="LID3" rel="#L3">3</span>
<span id="LID4" rel="#L4">4</span>
<span id="LID5" rel="#L5">5</span>
<span id="LID6" rel="#L6">6</span>
<span id="LID7" rel="#L7">7</span>
<span id="LID8" rel="#L8">8</span>
<span id="LID9" rel="#L9">9</span>
<span id="LID10" rel="#L10">10</span>
<span id="LID11" rel="#L11">11</span>
<span id="LID12" rel="#L12">12</span>
<span id="LID13" rel="#L13">13</span>
<span id="LID14" rel="#L14">14</span>
<span id="LID15" rel="#L15">15</span>
<span id="LID16" rel="#L16">16</span>
<span id="LID17" rel="#L17">17</span>
<span id="LID18" rel="#L18">18</span>
<span id="LID19" rel="#L19">19</span>
<span id="LID20" rel="#L20">20</span>
<span id="LID21" rel="#L21">21</span>
<span id="LID22" rel="#L22">22</span>
<span id="LID23" rel="#L23">23</span>
<span id="LID24" rel="#L24">24</span>
<span id="LID25" rel="#L25">25</span>
<span id="LID26" rel="#L26">26</span>
<span id="LID27" rel="#L27">27</span>
<span id="LID28" rel="#L28">28</span>
<span id="LID29" rel="#L29">29</span>
<span id="LID30" rel="#L30">30</span>
<span id="LID31" rel="#L31">31</span>
<span id="LID32" rel="#L32">32</span>
<span id="LID33" rel="#L33">33</span>
<span id="LID34" rel="#L34">34</span>
<span id="LID35" rel="#L35">35</span>
<span id="LID36" rel="#L36">36</span>
<span id="LID37" rel="#L37">37</span>
<span id="LID38" rel="#L38">38</span>
<span id="LID39" rel="#L39">39</span>
<span id="LID40" rel="#L40">40</span>
<span id="LID41" rel="#L41">41</span>
<span id="LID42" rel="#L42">42</span>
<span id="LID43" rel="#L43">43</span>
<span id="LID44" rel="#L44">44</span>
<span id="LID45" rel="#L45">45</span>
<span id="LID46" rel="#L46">46</span>
<span id="LID47" rel="#L47">47</span>
<span id="LID48" rel="#L48">48</span>
<span id="LID49" rel="#L49">49</span>
<span id="LID50" rel="#L50">50</span>
<span id="LID51" rel="#L51">51</span>
<span id="LID52" rel="#L52">52</span>
<span id="LID53" rel="#L53">53</span>
<span id="LID54" rel="#L54">54</span>
<span id="LID55" rel="#L55">55</span>
<span id="LID56" rel="#L56">56</span>
<span id="LID57" rel="#L57">57</span>
<span id="LID58" rel="#L58">58</span>
<span id="LID59" rel="#L59">59</span>
<span id="LID60" rel="#L60">60</span>
<span id="LID61" rel="#L61">61</span>
<span id="LID62" rel="#L62">62</span>
<span id="LID63" rel="#L63">63</span>
<span id="LID64" rel="#L64">64</span>
<span id="LID65" rel="#L65">65</span>
<span id="LID66" rel="#L66">66</span>
<span id="LID67" rel="#L67">67</span>
<span id="LID68" rel="#L68">68</span>
<span id="LID69" rel="#L69">69</span>
<span id="LID70" rel="#L70">70</span>
<span id="LID71" rel="#L71">71</span>
<span id="LID72" rel="#L72">72</span>
<span id="LID73" rel="#L73">73</span>
<span id="LID74" rel="#L74">74</span>
<span id="LID75" rel="#L75">75</span>
<span id="LID76" rel="#L76">76</span>
<span id="LID77" rel="#L77">77</span>
<span id="LID78" rel="#L78">78</span>
<span id="LID79" rel="#L79">79</span>
<span id="LID80" rel="#L80">80</span>
<span id="LID81" rel="#L81">81</span>
<span id="LID82" rel="#L82">82</span>
<span id="LID83" rel="#L83">83</span>
<span id="LID84" rel="#L84">84</span>
<span id="LID85" rel="#L85">85</span>
<span id="LID86" rel="#L86">86</span>
<span id="LID87" rel="#L87">87</span>
<span id="LID88" rel="#L88">88</span>
<span id="LID89" rel="#L89">89</span>
<span id="LID90" rel="#L90">90</span>
<span id="LID91" rel="#L91">91</span>
<span id="LID92" rel="#L92">92</span>
<span id="LID93" rel="#L93">93</span>
<span id="LID94" rel="#L94">94</span>
<span id="LID95" rel="#L95">95</span>
<span id="LID96" rel="#L96">96</span>
<span id="LID97" rel="#L97">97</span>
<span id="LID98" rel="#L98">98</span>
<span id="LID99" rel="#L99">99</span>
<span id="LID100" rel="#L100">100</span>
<span id="LID101" rel="#L101">101</span>
<span id="LID102" rel="#L102">102</span>
<span id="LID103" rel="#L103">103</span>
<span id="LID104" rel="#L104">104</span>
<span id="LID105" rel="#L105">105</span>
<span id="LID106" rel="#L106">106</span>
<span id="LID107" rel="#L107">107</span>
<span id="LID108" rel="#L108">108</span>
<span id="LID109" rel="#L109">109</span>
<span id="LID110" rel="#L110">110</span>
<span id="LID111" rel="#L111">111</span>
<span id="LID112" rel="#L112">112</span>
<span id="LID113" rel="#L113">113</span>
<span id="LID114" rel="#L114">114</span>
<span id="LID115" rel="#L115">115</span>
<span id="LID116" rel="#L116">116</span>
<span id="LID117" rel="#L117">117</span>
<span id="LID118" rel="#L118">118</span>
<span id="LID119" rel="#L119">119</span>
<span id="LID120" rel="#L120">120</span>
<span id="LID121" rel="#L121">121</span>
<span id="LID122" rel="#L122">122</span>
<span id="LID123" rel="#L123">123</span>
<span id="LID124" rel="#L124">124</span>
<span id="LID125" rel="#L125">125</span>
<span id="LID126" rel="#L126">126</span>
<span id="LID127" rel="#L127">127</span>
<span id="LID128" rel="#L128">128</span>
<span id="LID129" rel="#L129">129</span>
<span id="LID130" rel="#L130">130</span>
<span id="LID131" rel="#L131">131</span>
<span id="LID132" rel="#L132">132</span>
<span id="LID133" rel="#L133">133</span>
<span id="LID134" rel="#L134">134</span>
<span id="LID135" rel="#L135">135</span>
<span id="LID136" rel="#L136">136</span>
<span id="LID137" rel="#L137">137</span>
<span id="LID138" rel="#L138">138</span>
<span id="LID139" rel="#L139">139</span>
<span id="LID140" rel="#L140">140</span>
<span id="LID141" rel="#L141">141</span>
<span id="LID142" rel="#L142">142</span>
<span id="LID143" rel="#L143">143</span>
<span id="LID144" rel="#L144">144</span>
<span id="LID145" rel="#L145">145</span>
<span id="LID146" rel="#L146">146</span>
<span id="LID147" rel="#L147">147</span>
<span id="LID148" rel="#L148">148</span>
<span id="LID149" rel="#L149">149</span>
<span id="LID150" rel="#L150">150</span>
<span id="LID151" rel="#L151">151</span>
<span id="LID152" rel="#L152">152</span>
<span id="LID153" rel="#L153">153</span>
<span id="LID154" rel="#L154">154</span>
<span id="LID155" rel="#L155">155</span>
<span id="LID156" rel="#L156">156</span>
<span id="LID157" rel="#L157">157</span>
<span id="LID158" rel="#L158">158</span>
</pre>
          </td>
          <td width="100%">
            
              <div class="highlight"><pre><div class='line' id='LC1'><span class="cp">#include &lt;stdio.h&gt;</span></div><div class='line' id='LC2'><span class="cp">#include &lt;string.h&gt;</span></div><div class='line' id='LC3'><span class="cp">#include &lt;stdlib.h&gt;</span></div><div class='line' id='LC4'><span class="cp">#include &lt;sys/types.h&gt;</span></div><div class='line' id='LC5'><span class="cp">#include &lt;sys/stat.h&gt;</span></div><div class='line' id='LC6'><span class="cp">#include &lt;fcntl.h&gt;</span></div><div class='line' id='LC7'><span class="cp">#include &lt;sys/uio.h&gt;</span></div><div class='line' id='LC8'><span class="cp">#include &lt;unistd.h&gt;</span></div><div class='line' id='LC9'><br/></div><div class='line' id='LC10'><span class="cp">#define DEBUGf</span></div><div class='line' id='LC11'><span class="cp">#define MAXN 4294967295</span></div><div class='line' id='LC12'><br/></div><div class='line' id='LC13'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">gcd</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">a</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">b</span><span class="p">){</span></div><div class='line' id='LC14'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">gcd</span><span class="p">,</span> <span class="n">n1</span> <span class="o">=</span> <span class="n">abs</span><span class="p">(</span><span class="n">a</span><span class="p">),</span> <span class="n">n2</span> <span class="o">=</span> <span class="n">abs</span><span class="p">(</span><span class="n">b</span><span class="p">);</span></div><div class='line' id='LC15'>&nbsp;&nbsp;<span class="k">for</span> <span class="p">(</span><span class="n">gcd</span> <span class="o">=</span> <span class="p">(</span><span class="n">n1</span> <span class="o">&lt;</span> <span class="n">n2</span><span class="p">)</span> <span class="o">?</span> <span class="n">n1</span> <span class="o">:</span> <span class="n">n2</span><span class="p">;</span> <span class="n">gcd</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">;</span> <span class="n">gcd</span><span class="o">--</span><span class="p">)</span></div><div class='line' id='LC16'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="p">(</span><span class="n">n1</span> <span class="o">%</span> <span class="n">gcd</span> <span class="o">||</span> <span class="n">n2</span> <span class="o">%</span> <span class="n">gcd</span><span class="p">))</span></div><div class='line' id='LC17'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC18'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">gcd</span><span class="p">;</span></div><div class='line' id='LC19'><span class="p">}</span></div><div class='line' id='LC20'><br/></div><div class='line' id='LC21'><span class="kt">void</span> <span class="n">extended_euclid</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">a</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">b</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="o">*</span><span class="n">x</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="o">*</span><span class="n">y</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="o">*</span><span class="n">d</span><span class="p">)</span></div><div class='line' id='LC22'><span class="cm">/* calculates a * *x + b * *y = gcd(a, b) = *d */</span></div><div class='line' id='LC23'><span class="p">{</span></div><div class='line' id='LC24'>&nbsp;&nbsp;<span class="kt">long</span> <span class="n">q</span><span class="p">,</span> <span class="n">r</span><span class="p">,</span> <span class="n">x1</span><span class="p">,</span> <span class="n">x2</span><span class="p">,</span> <span class="n">y1</span><span class="p">,</span> <span class="n">y2</span><span class="p">;</span></div><div class='line' id='LC25'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">b</span> <span class="o">==</span> <span class="mi">0</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC26'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">d</span> <span class="o">=</span> <span class="n">a</span><span class="p">,</span> <span class="o">*</span><span class="n">x</span> <span class="o">=</span> <span class="mi">1</span><span class="p">,</span> <span class="o">*</span><span class="n">y</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC27'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span><span class="p">;</span></div><div class='line' id='LC28'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC29'>&nbsp;&nbsp;<span class="n">x2</span> <span class="o">=</span> <span class="mi">1</span><span class="p">,</span> <span class="n">x1</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">y2</span> <span class="o">=</span> <span class="mi">0</span><span class="p">,</span> <span class="n">y1</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC30'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">b</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC31'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">q</span> <span class="o">=</span> <span class="n">a</span> <span class="o">/</span> <span class="n">b</span><span class="p">,</span> <span class="n">r</span> <span class="o">=</span> <span class="n">a</span> <span class="o">-</span> <span class="n">q</span> <span class="o">*</span> <span class="n">b</span><span class="p">;</span></div><div class='line' id='LC32'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">*</span><span class="n">x</span> <span class="o">=</span> <span class="n">x2</span> <span class="o">-</span> <span class="n">q</span> <span class="o">*</span> <span class="n">x1</span><span class="p">,</span> <span class="o">*</span><span class="n">y</span> <span class="o">=</span> <span class="n">y2</span> <span class="o">-</span> <span class="n">q</span> <span class="o">*</span> <span class="n">y1</span><span class="p">;</span></div><div class='line' id='LC33'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">a</span> <span class="o">=</span> <span class="n">b</span><span class="p">,</span> <span class="n">b</span> <span class="o">=</span> <span class="n">r</span><span class="p">;</span></div><div class='line' id='LC34'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">x2</span> <span class="o">=</span> <span class="n">x1</span><span class="p">,</span> <span class="n">x1</span> <span class="o">=</span> <span class="o">*</span><span class="n">x</span><span class="p">,</span> <span class="n">y2</span> <span class="o">=</span> <span class="n">y1</span><span class="p">,</span> <span class="n">y1</span> <span class="o">=</span> <span class="o">*</span><span class="n">y</span><span class="p">;</span></div><div class='line' id='LC35'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC36'>&nbsp;&nbsp;<span class="o">*</span><span class="n">d</span> <span class="o">=</span> <span class="n">a</span><span class="p">,</span> <span class="o">*</span><span class="n">x</span> <span class="o">=</span> <span class="n">x2</span><span class="p">,</span> <span class="o">*</span><span class="n">y</span> <span class="o">=</span> <span class="n">y2</span><span class="p">;</span></div><div class='line' id='LC37'><span class="p">}</span></div><div class='line' id='LC38'><br/></div><div class='line' id='LC39'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">witness</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">a</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">n</span><span class="p">){</span></div><div class='line' id='LC40'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">d</span><span class="p">;</span></div><div class='line' id='LC41'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">b</span><span class="p">;</span></div><div class='line' id='LC42'>&nbsp;&nbsp;<span class="kt">long</span> <span class="n">c</span><span class="p">;</span></div><div class='line' id='LC43'>&nbsp;&nbsp;<span class="n">d</span><span class="o">=</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC44'>&nbsp;&nbsp;<span class="n">b</span><span class="o">=</span><span class="n">n</span><span class="o">-</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC45'>&nbsp;&nbsp;<span class="k">for</span><span class="p">(;</span> <span class="n">b</span><span class="o">!=</span><span class="mi">0</span><span class="p">;</span> <span class="n">b</span><span class="o">&gt;&gt;=</span><span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC46'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">b</span><span class="o">&amp;</span><span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC47'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">d</span> <span class="o">=</span> <span class="p">(</span><span class="n">d</span><span class="o">*</span><span class="n">a</span><span class="p">)</span><span class="o">%</span><span class="n">n</span><span class="p">;</span></div><div class='line' id='LC48'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC49'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">c</span> <span class="o">=</span> <span class="n">a</span><span class="p">;</span></div><div class='line' id='LC50'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">a</span> <span class="o">=</span> <span class="p">(</span><span class="n">a</span><span class="o">*</span><span class="n">a</span><span class="p">)</span><span class="o">%</span><span class="n">n</span><span class="p">;</span></div><div class='line' id='LC51'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">((</span><span class="n">a</span> <span class="o">==</span> <span class="mi">1</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">c</span> <span class="o">!=</span> <span class="mi">1</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">c</span> <span class="o">!=</span> <span class="n">n</span><span class="o">-</span><span class="mi">1</span><span class="p">))</span> <span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC52'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC53'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">d</span> <span class="o">==</span> <span class="mi">1</span><span class="p">)</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span> </div><div class='line' id='LC54'>&nbsp;&nbsp;<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC55'><span class="p">}</span></div><div class='line' id='LC56'>&nbsp;</div><div class='line' id='LC57'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">miller_rabin</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">n</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">s</span><span class="p">){</span></div><div class='line' id='LC58'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">i</span><span class="p">;</span></div><div class='line' id='LC59'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">a</span><span class="p">;</span></div><div class='line' id='LC60'>&nbsp;&nbsp;</div><div class='line' id='LC61'>&nbsp;&nbsp;<span class="k">for</span><span class="p">(</span><span class="n">i</span> <span class="o">=</span> <span class="mi">0</span> <span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">s</span> <span class="p">;</span> <span class="n">i</span><span class="o">++</span><span class="p">){</span></div><div class='line' id='LC62'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">a</span> <span class="o">=</span> <span class="n">rand</span><span class="p">()</span><span class="o">%</span><span class="p">(</span><span class="n">n</span><span class="o">-</span><span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC63'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">witness</span><span class="p">(</span><span class="n">a</span><span class="p">,</span> <span class="n">n</span><span class="p">)</span> <span class="o">==</span> <span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC64'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC65'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC66'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC67'>&nbsp;&nbsp;<span class="k">return</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC68'><span class="p">}</span></div><div class='line' id='LC69'><br/></div><div class='line' id='LC70'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">prime</span><span class="p">(</span><span class="kt">void</span><span class="p">){</span></div><div class='line' id='LC71'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">p</span><span class="p">;</span></div><div class='line' id='LC72'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC73'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">s</span> <span class="o">=</span> <span class="mi">1000</span><span class="p">;</span></div><div class='line' id='LC74'>&nbsp;&nbsp;<span class="k">while</span><span class="p">(</span><span class="n">i</span><span class="p">){</span></div><div class='line' id='LC75'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">p</span> <span class="o">=</span> <span class="n">rand</span><span class="p">()</span> <span class="o">%</span> <span class="mi">65536</span><span class="p">;</span></div><div class='line' id='LC76'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">i</span> <span class="o">=</span> <span class="o">!</span><span class="p">(</span><span class="n">miller_rabin</span><span class="p">(</span><span class="n">p</span><span class="p">,</span> <span class="n">s</span><span class="p">));</span></div><div class='line' id='LC77'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC78'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">p</span><span class="p">;</span></div><div class='line' id='LC79'><span class="p">}</span></div><div class='line' id='LC80'><br/></div><div class='line' id='LC81'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">prime_too</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">a</span><span class="p">){</span></div><div class='line' id='LC82'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">res</span><span class="p">;</span></div><div class='line' id='LC83'>&nbsp;&nbsp;<span class="n">res</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC84'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC85'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">res</span> <span class="o">=</span> <span class="n">rand</span><span class="p">()</span> <span class="o">%</span> <span class="mi">65536</span><span class="p">;</span></div><div class='line' id='LC86'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">gcd</span><span class="p">(</span><span class="n">a</span><span class="p">,</span> <span class="n">res</span><span class="p">)</span> <span class="o">==</span> <span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC87'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">res</span><span class="p">;</span></div><div class='line' id='LC88'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC89'>&nbsp;&nbsp;<span class="p">}</span> </div><div class='line' id='LC90'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">res</span><span class="p">;</span></div><div class='line' id='LC91'><span class="p">}</span></div><div class='line' id='LC92'><br/></div><div class='line' id='LC93'><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">crypt</span><span class="p">(</span><span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">d</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">e</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">n</span><span class="p">){</span></div><div class='line' id='LC94'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">r</span><span class="o">=</span><span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC95'>&nbsp;&nbsp;<span class="k">for</span><span class="p">(;</span> <span class="n">e</span> <span class="o">&gt;</span> <span class="mi">0</span> <span class="p">;</span> <span class="n">e</span> <span class="o">&gt;&gt;=</span> <span class="mi">1</span><span class="p">){</span></div><div class='line' id='LC96'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">((</span><span class="n">e</span><span class="o">%</span><span class="mi">2</span><span class="p">)</span><span class="o">==</span><span class="mi">1</span><span class="p">)</span> <span class="p">{</span></div><div class='line' id='LC97'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">r</span><span class="o">=</span><span class="p">(</span><span class="n">r</span><span class="o">*</span><span class="n">d</span><span class="p">)</span><span class="o">%</span><span class="n">n</span><span class="p">;</span></div><div class='line' id='LC98'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC99'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">d</span><span class="o">=</span><span class="p">(</span><span class="n">d</span><span class="o">*</span><span class="n">d</span><span class="p">)</span><span class="o">%</span><span class="n">n</span><span class="p">;</span></div><div class='line' id='LC100'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC101'>&nbsp;&nbsp;<span class="k">return</span> <span class="n">r</span><span class="p">;</span></div><div class='line' id='LC102'><span class="p">}</span></div><div class='line' id='LC103'><br/></div><div class='line' id='LC104'><br/></div><div class='line' id='LC105'><span class="kt">int</span> <span class="n">main</span><span class="p">(</span><span class="kt">int</span> <span class="n">argc</span><span class="p">,</span> <span class="kt">char</span> <span class="o">**</span><span class="n">argv</span><span class="p">){</span></div><div class='line' id='LC106'>&nbsp;&nbsp;<span class="kt">int</span> <span class="n">i</span><span class="p">,</span><span class="n">j</span><span class="p">,</span> <span class="n">r_size</span><span class="p">;</span></div><div class='line' id='LC107'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">tmp1</span><span class="p">,</span> <span class="n">tmp2</span><span class="p">;</span></div><div class='line' id='LC108'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">p</span><span class="p">,</span> <span class="n">q</span><span class="p">,</span> <span class="n">e</span><span class="p">,</span> <span class="n">d</span><span class="p">;</span></div><div class='line' id='LC109'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">phi</span><span class="p">,</span> <span class="n">n</span><span class="p">,</span> <span class="n">nn</span><span class="p">,</span> <span class="n">num</span><span class="p">,</span> <span class="n">encoded_num</span><span class="p">;</span></div><div class='line' id='LC110'>&nbsp;&nbsp;<span class="kt">unsigned</span> <span class="kt">long</span> <span class="kt">long</span> <span class="n">buf</span><span class="p">;</span></div><div class='line' id='LC111'>&nbsp;&nbsp;<span class="kt">FILE</span> <span class="o">*</span><span class="n">fid_keys</span><span class="p">;</span></div><div class='line' id='LC112'>&nbsp;&nbsp;<span class="kt">int</span> <span class="n">fid_in</span><span class="p">,</span> <span class="n">fid_out</span><span class="p">,</span> <span class="n">r_count</span><span class="p">;</span></div><div class='line' id='LC113'>&nbsp;&nbsp;<span class="n">fid_in</span> <span class="o">=</span> <span class="n">open</span><span class="p">(</span><span class="n">argv</span><span class="p">[</span><span class="mi">1</span><span class="p">],</span> <span class="n">O_RDONLY</span><span class="p">);</span></div><div class='line' id='LC114'>&nbsp;&nbsp;<span class="n">fid_out</span> <span class="o">=</span> <span class="n">open</span><span class="p">(</span><span class="n">argv</span><span class="p">[</span><span class="mi">2</span><span class="p">],</span> <span class="n">O_WRONLY</span> <span class="o">|</span> <span class="n">O_CREAT</span> <span class="o">|</span> <span class="n">O_TRUNC</span><span class="p">,</span> <span class="mo">00755</span><span class="p">);</span></div><div class='line' id='LC115'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">strcmp</span><span class="p">(</span><span class="n">argv</span><span class="p">[</span><span class="mi">3</span><span class="p">],</span> <span class="s">&quot;1&quot;</span><span class="p">)</span> <span class="o">==</span> <span class="mi">0</span><span class="p">){</span> <span class="cm">/*1 -- encode 0 - decode*/</span></div><div class='line' id='LC116'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">fid_keys</span> <span class="o">=</span> <span class="n">fopen</span><span class="p">(</span><span class="s">&quot;keys&quot;</span><span class="p">,</span> <span class="s">&quot;w&quot;</span><span class="p">);</span></div><div class='line' id='LC117'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">p</span> <span class="o">=</span> <span class="n">prime</span><span class="p">();</span></div><div class='line' id='LC118'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">q</span> <span class="o">=</span> <span class="n">prime</span><span class="p">();</span></div><div class='line' id='LC119'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">n</span> <span class="o">=</span> <span class="n">p</span><span class="o">*</span><span class="n">q</span><span class="p">;</span></div><div class='line' id='LC120'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">n</span> <span class="o">&gt;=</span> <span class="n">MAXN</span><span class="p">){</span></div><div class='line' id='LC121'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">p</span> <span class="o">=</span> <span class="n">prime</span><span class="p">();</span></div><div class='line' id='LC122'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">q</span> <span class="o">=</span> <span class="n">prime</span><span class="p">();</span></div><div class='line' id='LC123'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">n</span> <span class="o">=</span> <span class="n">p</span><span class="o">*</span><span class="n">q</span><span class="p">;</span></div><div class='line' id='LC124'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC125'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">phi</span> <span class="o">=</span> <span class="p">(</span><span class="n">p</span><span class="o">-</span><span class="mi">1</span><span class="p">)</span><span class="o">*</span><span class="p">(</span><span class="n">q</span><span class="o">-</span><span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC126'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">e</span> <span class="o">=</span> <span class="n">prime_too</span><span class="p">(</span><span class="n">phi</span><span class="p">);</span></div><div class='line' id='LC127'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">extended_euclid</span><span class="p">(</span><span class="n">e</span><span class="p">,</span> <span class="n">phi</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">d</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">tmp1</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">tmp2</span><span class="p">);</span></div><div class='line' id='LC128'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">d</span> <span class="o">=</span> <span class="n">d</span> <span class="o">%</span> <span class="n">phi</span><span class="p">;</span></div><div class='line' id='LC129'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">fprintf</span><span class="p">(</span><span class="n">fid_keys</span><span class="p">,</span> <span class="s">&quot;Secret key: %llu-%llu</span><span class="se">\n</span><span class="s">Public key: %llu-%llu</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">d</span><span class="p">,</span> <span class="n">n</span><span class="p">,</span> <span class="n">e</span><span class="p">,</span> <span class="n">n</span><span class="p">);</span></div><div class='line' id='LC130'>&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC131'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">fid_keys</span> <span class="o">=</span> <span class="n">fopen</span><span class="p">(</span><span class="s">&quot;keys&quot;</span><span class="p">,</span> <span class="s">&quot;r&quot;</span><span class="p">);</span></div><div class='line' id='LC132'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">fscanf</span><span class="p">(</span><span class="n">fid_keys</span><span class="p">,</span> <span class="s">&quot;Secret key: %llu-%llu</span><span class="se">\n</span><span class="s">Public key: %llu-%llu</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">d</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">n</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">e</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">n</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">4</span><span class="p">){</span><span class="n">puts</span><span class="p">(</span><span class="s">&quot;Make keys with param 1 first.&quot;</span><span class="p">);</span> <span class="n">exit</span><span class="p">(</span><span class="mi">0</span><span class="p">);};</span></div><div class='line' id='LC133'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC134'>&nbsp;&nbsp;<span class="n">nn</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span> <span class="n">r_size</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC135'>&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">nn</span> <span class="o">&lt;=</span> <span class="n">n</span><span class="p">)</span> <span class="p">{</span><span class="n">nn</span> <span class="o">&lt;&lt;=</span> <span class="mi">8</span><span class="p">;</span> <span class="n">r_size</span><span class="o">++</span><span class="p">;};</span></div><div class='line' id='LC136'>&nbsp;&nbsp;<span class="n">r_size</span> <span class="o">-=</span> <span class="mi">1</span><span class="p">;</span></div><div class='line' id='LC137'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">r_size</span> <span class="o">&lt;=</span> <span class="mi">0</span><span class="p">){</span><span class="n">puts</span><span class="p">(</span><span class="s">&quot;Error: Too small p, q. p*q must be bigger than 255.&quot;</span><span class="p">);</span> <span class="n">exit</span><span class="p">(</span><span class="mi">0</span><span class="p">);}</span></div><div class='line' id='LC138'>&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;%d</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">r_size</span><span class="p">);</span></div><div class='line' id='LC139'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">strcmp</span><span class="p">(</span><span class="n">argv</span><span class="p">[</span><span class="mi">3</span><span class="p">],</span> <span class="s">&quot;1&quot;</span><span class="p">)</span> <span class="o">==</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC140'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">num</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC141'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">read</span><span class="p">(</span><span class="n">fid_in</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">num</span><span class="p">,</span> <span class="n">r_size</span><span class="p">)</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC142'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">encoded_num</span> <span class="o">=</span> <span class="n">crypt</span><span class="p">(</span><span class="n">num</span><span class="p">,</span> <span class="n">d</span><span class="p">,</span> <span class="n">n</span><span class="p">);</span></div><div class='line' id='LC143'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">printf</span><span class="p">(</span><span class="s">&quot;%llu, %llu</span><span class="se">\n</span><span class="s">&quot;</span><span class="p">,</span> <span class="n">num</span><span class="p">,</span> <span class="n">encoded_num</span><span class="p">);</span></div><div class='line' id='LC144'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write</span><span class="p">(</span><span class="n">fid_out</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">encoded_num</span><span class="p">,</span> <span class="n">r_size</span> <span class="o">+</span> <span class="mi">1</span><span class="p">);</span></div><div class='line' id='LC145'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC146'>&nbsp;&nbsp;<span class="p">}</span><span class="k">else</span><span class="p">{</span></div><div class='line' id='LC147'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">encoded_num</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC148'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">while</span> <span class="p">(</span><span class="n">read</span><span class="p">(</span><span class="n">fid_in</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">encoded_num</span><span class="p">,</span> <span class="n">r_size</span> <span class="o">+</span> <span class="mi">1</span><span class="p">)</span> <span class="o">&gt;</span> <span class="mi">0</span><span class="p">){</span></div><div class='line' id='LC149'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">num</span> <span class="o">=</span> <span class="n">crypt</span><span class="p">(</span><span class="n">encoded_num</span><span class="p">,</span> <span class="n">e</span><span class="p">,</span> <span class="n">n</span><span class="p">);</span></div><div class='line' id='LC150'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">write</span><span class="p">(</span><span class="n">fid_out</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">num</span><span class="p">,</span> <span class="n">r_size</span><span class="p">);</span></div><div class='line' id='LC151'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC152'>&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC153'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">close</span><span class="p">(</span><span class="n">fid_in</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">0</span><span class="p">){</span><span class="n">perror</span><span class="p">(</span><span class="s">&quot;fid_in&quot;</span><span class="p">);</span> <span class="n">exit</span><span class="p">(</span><span class="mi">0</span><span class="p">);};</span></div><div class='line' id='LC154'>&nbsp;&nbsp;<span class="k">if</span> <span class="p">(</span><span class="n">close</span><span class="p">(</span><span class="n">fid_out</span><span class="p">)</span> <span class="o">&lt;</span> <span class="mi">0</span><span class="p">){</span><span class="n">perror</span><span class="p">(</span><span class="s">&quot;fid_out&quot;</span><span class="p">);</span> <span class="n">exit</span><span class="p">(</span><span class="mi">0</span><span class="p">);};</span></div><div class='line' id='LC155'>&nbsp;&nbsp;<span class="n">fclose</span><span class="p">(</span><span class="n">fid_keys</span><span class="p">);</span></div><div class='line' id='LC156'>&nbsp;&nbsp;<span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC157'><span class="p">}</span></div><div class='line' id='LC158'><br/></div></pre></div>
            
          </td>
        </tr>
      </table>
    
  </div>


      </div>
    </div>

  


    </div>
  
      

      <div class="push"></div>
    </div>

    <div id="footer">
      <div class="site">
        <div class="info">
          <div class="links">
            <a href="http://github.com/blog"><b>Blog</b></a> |
            <a href="http://support.github.com?sso=okIG4GFoQMnqXpGDcNIoAzGLIKnRnskTasTVPUOq4oWmm-Yo9mVjk379azVS_MPvnM5z5niHSn8JiriV0xMnQFP1D8Pb9jfmHf53pPxQTu0aQU_4JhbWXTMCXs6WTLbSGQxEZ71hO68TcQJ5yQtkGc1Jppnr_uZ7_mpoPyGOFcqn_vsnSAWoVUR42IawXfr1KFPWzrAWGq55iI7P8Bc7MsRsvI_EQUhqmaGr9lbsRCQ">Support</a> |
            <a href="http://github.com/training">Training</a> |
            <a href="http://github.com/contact">Contact</a> |
            <a href="http://develop.github.com">API</a> |
            <a href="http://status.github.com">Status</a> |
            <a href="http://twitter.com/github">Twitter</a> |
            <a href="http://help.github.com">Help</a> |
            <a href="http://github.com/security">Security</a>
          </div>
          <div class="company">
            &copy;
            2010
            <span id="_rrt" title="0.29047s from fe2.rs.github.com">GitHub</span> Inc.
            All rights reserved. |
            <a href="/site/terms">Terms of Service</a> |
            <a href="/site/privacy">Privacy Policy</a>
          </div>
        </div>
        <div class="sponsor">
          <div>
            Powered by the <a href="http://www.rackspace.com ">Dedicated
            Servers</a> and<br/> <a href="http://www.rackspacecloud.com">Cloud
            Computing</a> of Rackspace Hosting<span>&reg;</span>
          </div>
          <a href="http://www.rackspace.com">
            <img alt="Dedicated Server" src="http://assets2.github.com/images/modules/footer/rackspace_logo.png?afe70a1758c8408acd5e2f57bc6c24febb8ca721" />
          </a>
        </div>
      </div>
    </div>

    <script>window._auth_token = "d51e9c89c18a23268a7690251710925dec01091e"</script>
    

    <script type="text/javascript">
      _kmq.push(['trackClick', 'entice_banner_link', 'Entice banner clicked']);
      
    </script>
    
  </body>
</html>

