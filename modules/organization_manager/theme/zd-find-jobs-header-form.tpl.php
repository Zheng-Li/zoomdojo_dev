<!--<div class="dynamic-dropdown">-->
    <div class="front-top-block">
    <div class="front-tb-left">Search Jobs & Internships</div>
        <div class="front-tb-right">
            <form id="findJobsFormMini" action="/find-positions" method="get" >
                <div class="row-fluid" style="position:relative;right:90px;">
                    <input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type any keyword" class="keywords-autocomplete input-large span5" style="position:relative;margin-left:71px;width:304px;top:-1px;" required/>
                    <input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type location" class="location-autocomplete input-large span5" style="position:relative;margin-left:71px;width:304px;" />
                </div>
           </form>
            <a class="btn btn-danger btn-small fr-search-btn" style="float:right;position:relative;right:5%;top:-2px;" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Search</a>
       </div>
    </div>

