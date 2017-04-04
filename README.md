# Director
由于平时的空虚与寂寞无法忍耐，我们需要挖一个大小适中的坑，让自己没事儿的时候也别闲着。<p>我们需要做一个基于Actor模型的分布式系统，同时追求简单、小巧、高效、灵活&扩展性、脚本式。</p><h2></h2>
<p><strong>Director，需要满足一下的几个需求：</strong></p>
<li>Actor的逻辑通过Lua脚本实现。</li><li>Actor支持线程间通信与进程间通信（本地/远程），任何模式下使用方式透明。</li><li>实现&提供多个基础Actor，例如：Gateway、Router等</li><li>Lua使用的API库</li><li>Actor编辑器</li><li>分布式部署工具</li>
