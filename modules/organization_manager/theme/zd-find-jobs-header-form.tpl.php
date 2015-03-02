<div class="front-top-block">
    <div class="front-tb-left">Search Jobs & Internships:</div>
    <div class="front-tb-right">
        <form id="findJobsFormMini" action="/find-positions" method="get" >
            <div class="row-fluid" style="position:relative; right:90px;">
                <input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type any keywords" class="input-large span5 keywords-autocomplete" style=" margin-left:71px;width:304px;"/>
                <input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type location" class="input-large span5 location-autocomplete" style="margin-left:71px;width:304px;" />
            </div>
        </form>
        <a class="btn btn-danger btn-small fr-search-btn" style="position:relative; right:40px;" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Search</a>
    </div>
</div>