<div class="front-top-block">
    <div class="front-tb-left">Quick Search for Jobs</div>
    <div class="front-tb-right">
        <form id="findJobsFormMini" action="/find-positions" method="get">
            <div class="row-fluid">
                <input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type any keywords" class="fullwidth keywords-autocomplete"/>
                <input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type location" class="fullwidth location-autocomplete"/>
            </div>
        </form>
        <a class="btn btn-danger btn-small fr-search-btn" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Go</a>
    </div>
</div>